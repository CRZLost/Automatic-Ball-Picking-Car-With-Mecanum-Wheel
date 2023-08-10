/*
 *  Author:曹瑞泽
 *  Data:2023.6/7
 *  四川大学 2020级
 *
 * */

#include "Wheel_Speed_Control.h"
#include "debug.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "Serial.h"
#include "IMU_Driver.h"
#include "Bluetooth.h"
#include "PWM.h"
#include "Encoder.h"
#include "PID_Controller.h"
#include "DC_Motor.h"
#include "Camera.h"
#include "Power.h"
#include "Data_Central_Process.h"
#include "Timer.h"
#include "math.h"
#include  "Filter.h"

/************************************************************/
//全局变量区

     //车载时钟
    uint64_t Real_Time=0,Real_Time_ms=0,Current_Time=0;

    //Vofa通讯区域
    uint8_t Received_Data[8];  //蓝牙发出的指令数据
    float Plot_Data[10]; //通过Vofa传输数据给电脑
    float watch[8];//检测数据
    Serial_Election_t Serial_Election;//选择蓝牙串口
    char Control_Mode='A';

   //IMU模块
    IMU_DataSetTypedef IMU_DataSet; //IMU数据包
    uint8_t IMU_ReceiveData[28]; //IMU传来的反馈数据 由main统一声明
    Car_State_Tpyedef Car_State;
    float AngleZ_Store[2]={0}; //对IMU传来数据的储存

   //Camera模块
    char CameraData[12];//承接Openmv传来的原始数据流 由main函数统一声明；
    Camera_DataSet_Typedef Camera_DataSet;//解析Openmv得到的数据
    static float R_Theta[3]={0}; //地面极坐标系 [0]距离 [1]移动偏向角相对于Y轴 [2]朝向
    float Distance_Store[2]={0};

    //轮子驱动数据
    Wheel_Speed_Reference_Typedef Wheel_Speed_Reference; //轮子速度的预期值
    float Measured_Wheel_RPM[4]; //由Encoder得到的4轮RPM BL=[0] FL=[1] FR=[2] BR=[3] 作为Wheel_Speed_Control的反馈

    //动力管理
    Power_Manage_Typedef Power_Select;

    //流程标志区域
    uint8_t Spin_Flag=0,Rotate_Pause_Flag=0;


int main(void)
{

/************************************************************/
    //main函数的局部变量区
    int i;
    static float Velocity_Reference=0,Angular_Reference=0;//所需速度和角速度

/************************************************************/
    //函数初始化区
    SystemCoreClockUpdate();
    Delay_Init();
    IMU_Init();
    Bluetooth_Init();
    PWM_Init();
    Encoder_Init();
    DCMotor_Init();
    Camera_Init();
    Power_Manage_Init();
    Clock_Init();
    OLED_Init();



    while(1)
    {
      //静止 等待摄像头初始化完毕
      while(Real_Time<4)

      OLED_ShowString(1,1,"Preparing...");

/******************************************************************************/
     //能源管理
      Power_Select=Power_Wheel;
      Power_Manage(Power_Select,1);

//    Power_Select=Power_Motor;
//    Power_Manage(Power_Select,1);
/******************************************************************************/
    //命令解析 决定手控还是自控
    Vofa_Cmd_Analyze(&Control_Mode);

/******************************************************************************/
    //Openmv
    CameraData_Process(&Camera_DataSet); //解析摄像头传来的数据

/******************************************************************************/
    //IMU模块
    Position_Process(&IMU_DataSet);
//    State_Resolve(&IMU_DataSet,&Car_State,Real_Time);//给出当前的小车状态

/******************************************************************************/
    //信号滤波
    /*
     * 对输入信号进行滤波处理去除漂移
     * 但注意的是对航向角的增量及进行滤波处理 消除增量中的静态漂移
     */
    AngleZ_Store[0]=AngleZ_Store[1];
    AngleZ_Store[1]=IMU_DataSet.Angle_Z;
    IMU_DataSet.Angle_Z+=High_Pass_Filter(Real_Time_ms, Real_Time,(AngleZ_Store[1]-AngleZ_Store[0]),1);

    Distance_Store[0]=Distance_Store[1];
    Distance_Store[1]=Camera_DataSet.Distance;
    Camera_DataSet.Distance+=Low_Pass_Filter(Real_Time_ms, Real_Time,(Distance_Store[1]-Distance_Store[0]),0.2);

/******************************************************************************/
    //数据处理区域

    //模式选择区域
        if(Control_Mode=='A') //如果是’A‘由MCU自动解算
        {
            Camera_Control(R_Theta,&Velocity_Reference,Real_Time,Real_Time_ms,&IMU_DataSet,&Camera_DataSet,&Spin_Flag,&Rotate_Pause_Flag);
            Rotate_PID_Controller(R_Theta,IMU_DataSet.Angle_Z,&Angular_Reference,Spin_Flag,Rotate_Pause_Flag,0.1,-0.1);
        }


        if(Control_Mode=='M')//如果是M由人给指令
        {
             Manual_Control(&Velocity_Reference, R_Theta);
             Spin_Flag=0;
             Rotate_PID_Controller(R_Theta,IMU_DataSet.Angle_Z,&Angular_Reference,Spin_Flag,Rotate_Pause_Flag,0.628,-0.628);

        }


        if(Control_Mode=='S')//紧急制动
        {
            Velocity_Reference=0;
            Angular_Reference=0;
            Power_Select=Power_Wheel;
            Power_Manage(Power_Select,0);
            Spin_Flag=0;
            Rotate_PID_Controller(R_Theta,IMU_DataSet.Angle_Z,&Angular_Reference,Spin_Flag,Rotate_Pause_Flag,0.628,-0.628); //旋转对应的PID 输入角度Error输出旋转速
        }
        else
        {
            Power_Select=Power_Wheel;
            Power_Manage(Power_Select,1);
        }





    //分配速度矩阵
    Velocity_Distribution(&Wheel_Speed_Reference,&Velocity_Reference,&Angular_Reference,R_Theta,1);//Scale由PID输出

/******************************************************************************/
    //轮子控制区域
    Wheel_Speed_Control(&Wheel_Speed_Reference,Measured_Wheel_RPM); //轮子旋转速度的PID控制
                                                                    //轮子平移速度的PID控制 可以考虑对加速度计进行低通滤波 如果时间允许的情况

/******************************************************************************/
    //蓝牙通讯处理区

        //获得监视数据
         if(Control_Mode=='M')
         {
             watch[0]=1;
         }
         else
         {
             watch[0]=2;
         }


         watch[1]=Wheel_Speed_Reference.FR_RPM;
         watch[2]=Measured_Wheel_RPM[2];
         watch[3]=*(R_Theta+2);
         watch[4]=IMU_DataSet.Angle_Z;

        for(i=0;i<4;i++)
        {
          *(Plot_Data+i)= *(watch+i);
        }
        Serial_Election=Serial3;//蓝牙串口选择
        Plot(Serial_Election,Plot_Data,4);//无线通讯发送数据

    }


}



/************************************************************/
//中断函数区 用来产生PWM波
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast"))); //防止出现只有一次中断
void TIM2_IRQHandler(void)
{
    if(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update)==1) //获取中断标志
    {
       Encoder_Get_Wheel_RPM(Measured_Wheel_RPM);
       Clear_Encoder();
       TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除中断标志
    }
}


//配置中断函数 用来计时
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast"))); //防止出现只有一次中断
void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetFlagStatus(TIM1, TIM_FLAG_Update)==1)
    {
        Real_Time_ms+=1;
        if(Real_Time_ms==1000)
        {
            Real_Time+=1;
            Real_Time_ms=0;
        }
        TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    }
}

