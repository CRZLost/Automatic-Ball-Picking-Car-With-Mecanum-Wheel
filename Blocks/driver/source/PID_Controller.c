/*
 * PID_Controller.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */


#include "debug.h"                 // Device header
#include "PID_Controller.h"

//(*Error)[3] 指针型数组 储存行指针数据  [3]:每个行指针囊括3个列指针  Error[1]+1 第二行第二列
void Wheel_PID_Controller(PID_Parameter* Parameter,double (*Error)[3],double* Output,int32_t UpperLimit,int32_t LowerLimit)
{
    //对于行来说 BL=[0] FL=[1] FR=[2] BR=[3]对于列来说是储存的数据
    static double Portion_Kp[4][10];
    static double Portion_Ki[4][10];
    static double Portion_Kd[4][10];
    double Portion_Kp_Sum[4]={0,0,0,0};
    double Portion_Kp_Ave[4]={0,0,0,0};
    double Portion_Ki_Sum[4]={0,0,0,0};
    double Portion_Ki_Ave[4]={0,0,0,0};
    double Portion_Kd_Sum[4]={0,0,0,0};
    double Portion_Kd_Ave[4]={0,0,0,0};
    double Increment[4]={0,0,0,0};
    uint16_t i,j;
    static uint32_t Add_Count[4]={0};


    //分别储存10词数据求和取平均去除毛刺现象
    for(i=0;i<4;i++)
    {
        for(j=0;j<10;j++)
           {
               if(j<8)
               {
                   Portion_Kp[i][j]=Portion_Kp[i][j+1];
                   Portion_Ki[i][j]=Portion_Ki[i][j+1];
                   Portion_Kd[i][j]=Portion_Kd[i][j+1]; //位置移位
                   Portion_Kp_Sum[i]+=Portion_Kp[i][j];
                   Portion_Ki_Sum[i]+=Portion_Ki[i][j];
                   Portion_Kd_Sum[i]+=Portion_Kd[i][j]; //求和
               }
               else
               {
                   Portion_Kp[i][j]=Parameter->Kp*(*(*(Error+i)+2)-*(*(Error+i)+1)); //先访问行 再访问列
                   Portion_Ki[i][j]=Parameter->Ki*(*(*(Error+i)+2));
                   Portion_Kd[i][j]=Parameter->Kd*(*(*(Error+i)+2)-2*(*(*(Error+i)+1))+*(*(Error+i)));
                   Portion_Kp_Sum[i]+=Portion_Kp[i][j];
                   Portion_Ki_Sum[i]+=Portion_Ki[i][j];
                   Portion_Kd_Sum[i]+=Portion_Kd[i][j];
               }
           }

        Portion_Kp_Ave[i]=Portion_Kp_Sum[i]/10;
        Portion_Ki_Ave[i]=Portion_Ki_Sum[i]/10;
        Portion_Kd_Ave[i]=Portion_Kd_Sum[i]/10;
        Increment[i]=Portion_Kp_Ave[i]+Portion_Ki_Ave[i]+Portion_Kd_Ave[i]; //步进
        *(Output+i)=*(Output+i)+Increment[i];
        //设置输出的上下限
        if(*(Output+i)>UpperLimit)
        {
            *(Output+i)=UpperLimit;
        }
        if(*(Output+i)<LowerLimit)
        {
            *(Output+i)=LowerLimit;
        }

        //消除静止时的无法推动轮胎的小量Speed_Cmd

       if(Add_Count[i]<50&&(*(Output+i)>-60&&*(Output+i)<60))
       {
           Add_Count[i]+=1;
       }
       if(Add_Count[i]>50&&(*(Output+i)>-60&&*(Output+i)<60))
       {
           *(Output+i)=0;
           Add_Count[i]=0;
       }
    }



}




void Rotate_PID_Controller(float* R_Theta,float Current_Orient,float* Angular_Reference,uint8_t Spin_Flag,uint8_t Rotate_Pause_Flag,float UpperLimit,float LowerLimit)
{
    int i;
    static uint8_t flag=1;
    static double Theta_Error[3];
    static double Portion_Kp[10];
    static double Portion_Ki[10];
    static double Portion_Kd[10];
    double Portion_Kp_Sum={0};
    double Portion_Kp_Ave={0};
    double Portion_Ki_Sum={0};
    double Portion_Ki_Ave={0};
    double Portion_Kd_Sum={0};
    double Portion_Kd_Ave={0};
    double Increment={0};


    //初始化误差储存
    if(flag)
    {
        for(i=0;i<3;i++)
        {
           Theta_Error[i]=0;
        }
    }flag=0;

    //PID参数赋值
    PID_Parameter Rotate_PID;
    Rotate_PID.Kp=0.0052;
    Rotate_PID.Ki=0.00004;
    Rotate_PID.Kd=0.002;

    //计算Error
    for(i=0;i<2;i++)
    {
      Theta_Error[i]=Theta_Error[i+1]; //误差传递
    }
    Theta_Error[2]=*(R_Theta+2)-Current_Orient; //本次误差


    //!!!!!!!!临界值问题尚未解决
    if(Theta_Error[2]>180)
    {
        Theta_Error[2]=-(360-Theta_Error[2]);//防止走优弧
    }
    if(Theta_Error[2]<-180)
    {
        Theta_Error[2]=360+Theta_Error[2];
    }

    for(i=0;i<10;i++)
    {
       if(i<8)
       {
           Portion_Kp[i]=Portion_Kp[i+1];
           Portion_Ki[i]=Portion_Ki[i+1];
           Portion_Kd[i]=Portion_Kd[i+1]; //位置移位
           Portion_Kp_Sum+=Portion_Kp[i];
           Portion_Ki_Sum+=Portion_Ki[i];
           Portion_Kd_Sum+=Portion_Kd[i]; //求和
       }
       else
       {
           Portion_Kp[i]=Rotate_PID.Kp*(*(Theta_Error+2)-*(Theta_Error+1)); //先访问行 再访问列
           Portion_Ki[i]=Rotate_PID.Ki*(*(Theta_Error+2));
           Portion_Kd[i]=Rotate_PID.Kd*(*(Theta_Error+2)-2*(*(Theta_Error+1))+*(Theta_Error));
           Portion_Kp_Sum+=Portion_Kp[i];
           Portion_Ki_Sum+=Portion_Ki[i];
           Portion_Kd_Sum+=Portion_Kd[i];
       }
     }

        Portion_Kp_Ave=Portion_Kp_Sum/10;
        Portion_Ki_Ave=Portion_Ki_Sum/10;
        Portion_Kd_Ave=Portion_Kd_Sum/10;
        Increment=Portion_Kp_Ave+Portion_Ki_Ave+Portion_Kd_Ave; //步进
        *Angular_Reference+=Increment;
        //设置输出的上下限
        if(*Angular_Reference>UpperLimit)//rad/s
        {
            *Angular_Reference=UpperLimit;
        }
        if(*Angular_Reference<LowerLimit)
        {
            *Angular_Reference=LowerLimit;
        }

        if(*(Theta_Error+2)<3&&*(Theta_Error+2)>-3)//判断阈值
        {
            *Angular_Reference=0;
        }

        Portion_Ki_Sum=0;
        Portion_Kd_Sum=0;
        Portion_Ki_Sum=0;

        if(Spin_Flag)
        {
            *Angular_Reference=0.2; //Search阶段 恒定角速度旋转
            Clear_Data(Theta_Error,3); //避免开启瞬间的储存误差带来的干扰
            Clear_Data(Portion_Kd,10);
            Clear_Data(Portion_Ki,10);
            Clear_Data(Portion_Kp,10);
        }

        if(Rotate_Pause_Flag)
        {
            *Angular_Reference=0;
            Clear_Data(Theta_Error,3);
            Clear_Data(Portion_Kd,10);
            Clear_Data(Portion_Ki,10);
            Clear_Data(Portion_Kp,10);
        }

}


void Clear_Data(double* Data,uint8_t Size)
{
    uint8_t i;
    for(i=0;i<Size;i++)
    {
        *(Data+i)=0;
    }
}


