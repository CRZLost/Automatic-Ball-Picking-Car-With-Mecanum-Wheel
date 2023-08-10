/*
 * Data_Central_Process.c
 *
 *  Created on: Jun 29, 2023
 *      Author: Lost
 */

#include "Camera.h"
#include "math.h"
#include "debug.h"
#include "IMU_Driver.h"
#include "Data_Central_Process.h"
#include "Wheel_Speed_Control.h"
#include "Power.h"

extern uint8_t Received_Data[8];  //蓝牙发出的指令数据
extern float watch[8];


//根据摄像头传来的数据解析出平面的r theta
void Gain_R_Theta(Camera_DataSet_Typedef* Camara_DataSet,float* R_Theta)
{
        // +0为R +1为Theta
     *R_Theta=sqrtf(pow(Platform_Length,2)+pow(Camara_DataSet->Distance,2)-pow(Camera_Height,2));
     *(R_Theta+1)=Camara_DataSet->Theta-90; //平移朝向
     *(R_Theta+2)=Camara_DataSet->Theta-90; //小车朝向
}






//void Gain_Reference(float* R_Theta,uint32_t* Stage_Flag,float* Velocity_Reference,float* Angular_Reference,uint8_t* Event_Flag)
//{
//    static uint8_t V_Flag,W_Flag,TimePin=0,TimePin2=0;
//    double Distance_Ratio,Angular_Ratio;
//    static uint8_t Wait_Flag=0,Pick_Flag=0;
//    static double Original_Distance,Original_Theta; //初始的距离 角度
//    static double Current_Time;
//
//    Current_Time=Real_Time*1000+Real_Time_ms;
//
//    //根据所处阶段对V和W的flag分别赋值   flag=1由函数控制 flag=0直接赋值控制
//    switch (*Stage_Flag)
//    {
//        case 1: //Found阶段 本阶段小车停止任何动作2s以获得摄像头稳定的数据 摄像头有权限
//            V_Flag=0;W_Flag=0;//切断函数输出
//            Wait_Flag+=1;//等待标志
//            *Velocity_Reference=0; *Angular_Reference=0;//直接赋值
//            break;
//
//        case 2://Approach阶段 本阶段小车直线靠近乒乓球 不做旋转动作 摄像头有权限
//            V_Flag=1;W_Flag=0;
//            break;
//
//        case 3://Spin阶段 本阶段小车进行旋转对齐小球 摄像头有权限
//            V_Flag=0;W_Flag=1;
//                 break;
//
//        case 4://Pick阶段 本阶段小车进行小球的拾起动作 摄像头无权限
//            V_Flag=0;W_Flag=0;//切断函数输出
//            Pick_Flag+=1;//等待标志
//            *Velocity_Reference=Pick_Velocity; *Angular_Reference=0;//直接赋值
//                 break;
//
//        case 5://Search阶段 本阶段小车原地旋转寻找下一个小球  摄像头无权限
//            V_Flag=0;W_Flag=0;//切断函数输出
//            *Velocity_Reference=0;*Angular_Reference=Search_Angula_Speed;
//                 break;
//
//        case 6://Stop阶段小车原地精致
//          V_Flag=0;W_Flag=0;//切断函数控制
//          *Velocity_Reference=0; *Angular_Reference=0;//直接赋值
//               break;
//
//        default:
//            break;
//    }
//
//
//    //负责Found->Approach
//    if(Wait_Flag==1)//如果存在等待需求 储存此时的RealTime 仅第一次处于found状态时纪录时间
//    {
//        TimePin=Real_Time*1000+Real_Time_ms;
//    }
//    if((Current_Time-TimePin)>2000&&*Stage_Flag==1) //如果Found阶段等待2s后 进入Approach阶段 清除waitCount 同时记录初始距离和初始角度
//    {
//        *Stage_Flag=2;
//        TimePin=0;
//        Original_Distance=*R_Theta;
//        Original_Theta=*(R_Theta+1); //平移角度
//        Wait_Flag=0;
//    }
//


//
//    //距离规划
//    Distance_Ratio=*(R_Theta)/(Original_Distance-Distance_Threshold);
//    if(Distance_Ratio<0.1)
//    {
//        *Velocity_Reference=-Maximum_Velocity*(Distance_Ratio)*(Distance_Ratio-0.1)*V_Flag;
//    }
//    if(0.1<Distance_Ratio&&Distance_Ratio<0.9)
//    {
//        *Velocity_Reference=Maximum_Velocity*V_Flag;
//    }
//    if(Distance_Ratio>0.9)
//    {
//        *Velocity_Reference=-Maximum_Velocity*(Distance_Ratio-0.9)*(Distance_Ratio-1)*V_Flag;
//    }
//
//    if(Distance_Ratio>1&&*Stage_Flag==2) //别忘&上个Stage的标志 确保是从上一个阶段到达
//    {
//        *Stage_Flag=3; //Approach->Spin !!!!!!!此处或许加一个短暂停顿
//    }
//
//
//
//    //角度规划
//    Angular_Ratio=(*(R_Theta+1)-90)/(Original_Theta-90);
//    if(Angular_Ratio<0.1)
//    {
//        *Angular_Reference=-Maximum_Angular*(Angular_Ratio)*(Angular_Ratio-0.1)*W_Flag;
//    }
//    if(Angular_Ratio>0.1&&Angular_Ratio<0.9)
//    {
//       *Angular_Reference=Maximum_Angular*W_Flag;
//    }
//    if(Angular_Ratio>0.9)
//    {
//        *Angular_Reference=-Maximum_Angular*(Angular_Ratio-0.9)*(Angular_Ratio-1)*W_Flag;
//    }
//    //赋予旋转正负
//    if((Original_Theta-90)<0&&W_Flag)
//    {
//        *Angular_Reference=-*Angular_Reference;
//    }
//
//    if(Angular_Ratio>1&&*Stage_Flag==3)
//    {
//       *Stage_Flag=4; //Spin->Pick
//    }
//
//
//    if(Pick_Flag==1)//如果存在等待需求 储存此时的RealTime 仅第一次处于Pick状态时纪录时间
//    {
//          TimePin2=Real_Time;
//    }
//    if((Real_Time-TimePin2)>Pick_Duration&&*Stage_Flag==4)
//    {
//       *Stage_Flag=5; //Pick->Search
//        TimePin2=0;
//        Pick_Flag=0;
//        *Event_Flag=0; //流程被执行完毕
//    }
//
//}


void State_Resolve(IMU_DataSetTypedef* IMUDataSet,Car_State_Tpyedef* Car_State,uint64_t Real_Time)
{
    uint8_t i;
    static float Vx_Increment[10],Vy_Increment[10],Angular_Speed[10],Orient[10],Time_Increment;
    static float Vx_Sum,Vy_Sum,Angular_Speed_Sum,Orient_Sum;
    static uint64_t Last_Monment=0;

    //取平均消除抖动
    for(i=0;i<8;i++)
    {
        Vx_Increment[i]=Vx_Increment[i+1];
        Vy_Increment[i]=Vy_Increment[i+1];
        Angular_Speed[i]=Angular_Speed[i+1];
        Orient[i]=Orient[i+1];
        Vx_Sum+=Vx_Increment[i];
        Vy_Sum+=Vy_Increment[i];
        Orient_Sum+=Orient[i];
        Angular_Speed_Sum+=Angular_Speed[i];
    }

    Time_Increment=Real_Time-Last_Monment; //算出时间间隔

    Vx_Increment[9]=IMUDataSet->Accerelation_X*Time_Increment;
    Vy_Increment[9]=IMUDataSet->Accerelation_Y*Time_Increment;
    Angular_Speed[9]=IMUDataSet->Angular_Speed_Z;
    Orient[9]=IMUDataSet->Angle_Z;


    Car_State->Vx+=(Vx_Sum+Vx_Increment[9])/10;
    Car_State->Vy+=(Vy_Sum+Vy_Increment[9])/10;
    Car_State->Wz+=(Angular_Speed_Sum+Angular_Speed[9])/10;
    Car_State->Orient=(Orient_Sum+Orient[9])/10;

    //sum清零
    Vx_Sum=0;
    Vy_Sum=0;
    Orient_Sum=0;
    Angular_Speed_Sum=0;

    Last_Monment=Real_Time;//储存空间

}

void Velocity_Distribution(Wheel_Speed_Reference_Typedef* Wheel_Speed_Reference,float* Velocity_Reference,float* Angular_Reference,float* R_Theta,float Scale)
{
    float W_Vector[4];
    float Vx=-*Velocity_Reference*(sin(0.017453**(R_Theta+1)));
    float Vy=*Velocity_Reference*(cos(0.017453**(R_Theta+1)));
    float W=*Angular_Reference;

    //矩阵反解 *60/R 是从mm/s转为rpm
     W_Vector[0]=(-Vx+Vy-(Rx+Ry)*W)/R*60;
     W_Vector[1]=(Vx+Vy-(Rx+Ry)*W)/R*60;
     W_Vector[2]=(-Vx+Vy+(Rx+Ry)*W)/R*60;
     W_Vector[3]=(Vx+Vy+(Rx+Ry)*W)/R*60;

    //Scale由整车PID控制
    Wheel_Speed_Reference->FL_RPM=-Scale*W_Vector[0];
    Wheel_Speed_Reference->BL_RPM=-Scale*W_Vector[1]; //注意左右两次的正负相反
    Wheel_Speed_Reference->BR_RPM=Scale*W_Vector[2];
    Wheel_Speed_Reference->FR_RPM=Scale*W_Vector[3];

}


void Manual_Control(float* Velocity_Reference,float* R_Theta)
{
    float Vx=0,Vy=0;
    float Judge=*(float*)(Received_Data);

    if(Judge==1500)//确定为方向赋值
    {
        *(R_Theta+2)=-*((float*)Received_Data+1); //朝向赋值
    }
    else //为速度赋值
    {
         Vx=*(float*)(Received_Data);///1000*Maximum_Velocity
         Vy=*((float*)Received_Data+1);///1000*Maximum_Velocity
         if(Vx>400||Vy>400||Vx<-400||Vy<-400) //消除切换模式时的突变
         {
             Vx=0;
             Vy=0;
         }
         *(R_Theta+1)=57.296*atan(Vx/Vy); //在最后一步之前同一用°
         if(Vy==0&&(Vx>0|Vx==0))
         {
             *(R_Theta+1)=0;
         }
         if(Vy==0&&Vx<0)
         {
             *(R_Theta+1)=180;
         }
         if(Vy<0)
         {
             *(R_Theta+1)+=180; //反方向取反
         }
         *Velocity_Reference=sqrt(Vx*Vx+Vy*Vy);
    }
}


/*
 *
 * 负责Found------>Search Search->Found的阶段控制
 * R_Theta[0] 直线距离    R_Theta[1] 平移与Y轴夹角   R_Theta[2] 朝向
 * Stage_Flag所处阶段标志
 * Velocity_Reference 平移速度的期望值
 * Angular_Reference 旋转速度的期望值
 * Event_Flag 发现小球事件标志位
*/
void Camera_Control(float* R_Theta,float* Velocity_Reference,float Real_Time_s,float Real_Time_ms,IMU_DataSetTypedef* IMU_DataSet,Camera_DataSet_Typedef* Camara_DataSet,uint8_t* Spin_Flag,uint8_t* Rotate_Pause_Flag)
{

    uint8_t i;
    static uint8_t Stage_Flag=1,Wait_Flag=0;; //初始为Search阶段
    static uint8_t Event_Flag=0,Found_Count=0,Lost_Count=0;
    static uint64_t Current_Time,Time_Pin;
    static uint8_t Exist_Check=0; //时刻检查存在的标志
    static double Original_Distance,Distance_Ratio;
    static float Distance_Store={0};
    static float Original_Distance_Store[40]={0};
    Power_Manage_Typedef Power_Select;

    Current_Time=Real_Time_ms+Real_Time_s*1000; //当前时间

/**********************************************************/
    //不断获取当前摄像头传来的位置信息
    if(Camara_DataSet->Distance>0)
    {
        *R_Theta=fabsf(sqrtf(pow(Camara_DataSet->Distance/10,2)+pow(Camera_Height,2)-pow(Platform_Length,2)));
        if(*(R_Theta)==0||*(R_Theta)>10000||*(R_Theta)<0)
        {
            *R_Theta=Distance_Store;
        }
        else
        {
            Distance_Store=*R_Theta;
        }
    }
    else
    {
        *R_Theta=Distance_Store;
    }

/**********************************************************/
    //判定是否要开始一次流程
    if(Event_Flag==0)
    {
        Stage_Flag=1; //未找到时为Search阶段
        if(Camara_DataSet->Distance>0&&Found_Count<3)
        {
            Found_Count++;
        }

        if(Found_Count>2)
        {
            Found_Count=0;Stage_Flag=2;*Rotate_Pause_Flag=1; //进入下一阶段Found阶段 开启一次流程
            Event_Flag=1;//开启一次流程 此时置1 全流程走完后清零
            Exist_Check=1;
        }
    }


    if(Camara_DataSet->Distance<0&&Stage_Flag<4) //Stage=4后关闭摄像头的检查功能
    {
        Lost_Count++;
        if(Lost_Count>20)
        {
            Exist_Check=0;
            Event_Flag=0; //流程终止
            Lost_Count=0;
        }

    }

    if(Camara_DataSet->Distance>0&&Lost_Count<19) //重寻回机制
    {
        Lost_Count=0;
    }

/**********************************************************/
    //各个阶段的控制语句

    if(Stage_Flag==1) //Search阶段
    {
        *Spin_Flag=1; //开始自旋转
        *Rotate_Pause_Flag=0;
        *(R_Theta+1)=0;
        *Velocity_Reference=0;
    }

    if(Stage_Flag==2) //Found阶段
    {
        *Spin_Flag=0;
        *(R_Theta+1)=0;
        *Velocity_Reference=0;

        if(Wait_Flag==0)
        {
            Wait_Flag=1;
            Time_Pin=Current_Time;
        }

        if(Wait_Flag==1&&Stage_Flag==2)
        {
            for(i=0;i<39;i++)
            {
               Original_Distance_Store[i]=Original_Distance_Store[i+1]; //储存等待期间的Distance
            }
            Original_Distance_Store[39]=*(R_Theta);

        }


        if((Current_Time-Time_Pin)>2000&&Wait_Flag==1&&Stage_Flag==2) //时间间距内记录数据
        {
            if(Camara_DataSet->Distance>0)
            {
                Original_Distance=Find_Max(Original_Distance_Store,40);//记录初始距离
            }

            for(i=0;i<40;i++)
            {
                Original_Distance_Store[i]=0; //清除储存
            }

            *Rotate_Pause_Flag=0; //开启旋转
            Wait_Flag=0;  //停止等待阶段
            Stage_Flag=3; //进入Approach阶段
        }

    }



//    if(Stage_Flag==3&&Event_Flag==1) //锁定球的朝向
//    {
//        *(R_Theta+2)=IMU_DataSet->Angle_Z+Camara_DataSet->Theta-90; //摄像头控制旋转
//    }



    //Approach 阶段
    if(Stage_Flag==3)
    {


        //距离规划
       Distance_Ratio=(Original_Distance-*(R_Theta))/(Original_Distance-Distance_Threshold);

       if(Distance_Ratio<0.2)
       {
           *Velocity_Reference=-Maximum_Velocity*(Distance_Ratio-0.2)*(Distance_Ratio)+20;
           *(R_Theta+2)=IMU_DataSet->Angle_Z+Camara_DataSet->Theta-90; //初始角度值
       }


       if(0.2<Distance_Ratio&&Distance_Ratio<0.9)
       {
           *Velocity_Reference=Maximum_Velocity;
           *(R_Theta+2)=IMU_DataSet->Angle_Z+Camara_DataSet->Theta-90; //摄像头控制旋转
//           *(Rotate_Pause_Flag)=0;
       }


       if(Distance_Ratio>0.9)
       {
           *Velocity_Reference=-Maximum_Velocity*(Distance_Ratio-0.9)*(Distance_Ratio-1)+40;
           *(R_Theta+2)=IMU_DataSet->Angle_Z+Camara_DataSet->Theta-90; //摄像头控制旋转
       }

       if(Distance_Ratio>1&&Stage_Flag==3&&Wait_Flag==0) //别忘&上个Stage的标志 确保是从上一个阶段到达
       {
         Wait_Flag=1;
         Time_Pin=Current_Time;
       }

       if(Wait_Flag==1&&Stage_Flag==3)
       {
           *Velocity_Reference=0; //停顿
       }
       if(Wait_Flag==1&&(Current_Time-Time_Pin)>2000&&Stage_Flag==3)
       {
           Wait_Flag=0;
           Stage_Flag=4;//进入下阶段Pick阶段
           *Rotate_Pause_Flag=1; //暂停旋转功能
       }
    }

    //Pick阶段
    if(Stage_Flag==4)
    {

        if(Wait_Flag==0)
        {
            //开始往前走
            *Rotate_Pause_Flag=0;
            Time_Pin=Current_Time; //标记时间
            Wait_Flag=1;
            *Velocity_Reference=Pick_Velocity;
            *(R_Theta+1)=0;
            Power_Select=Power_Motor;
            Power_Manage(Power_Select,1);

        }

        if(Wait_Flag==1&&Current_Time-Time_Pin>Pick_Duration)
        {
            Power_Select=Power_Motor;
            Power_Manage(Power_Select,0);
            Wait_Flag=0;
            Event_Flag=0; //清除事件标志 开始新一轮循环
        }
    }

}



float Find_Max(float* Data,uint8_t Size)
{
    uint8_t i;
    float MaxValue=0;

    for(i=0;i<Size;i++)
    {
        if(MaxValue<*(Data+i))
        {
            MaxValue=*(Data+i);
        }
    }

    return MaxValue;
}








