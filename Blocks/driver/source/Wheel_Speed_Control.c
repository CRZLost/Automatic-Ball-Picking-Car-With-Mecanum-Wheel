/*
 * Wheel_Speed_Control.c
 *
 *  Created on: Jun 24, 2023
 *      Author: Lost
 */

#include "Wheel_Speed_Control.h"
#include "PID_Controller.h"
#include "debug.h"
#include "DC_Motor.h"


void Wheel_Speed_Control(Wheel_Speed_Reference_Typedef* Wheel_Speed_Reference,float* Measured_Wheel_RPM)
{

    int i,j;
    static double Wheel_Speed_Error[4][3],flag=1; //行BL=[0] FL=[1] FR=[2] BR=[3] 列为时间线的储存
    static double Output[4];//行BL=[0] FL=[1] FR=[2] BR=[3] 列为时间线的储存
    Wheel_Speed_Typdef Wheel_Speed;

    /*
     * static修饰Error 防止Error数据丢失 储存上次和上上次的error 4代表4个轮子 3代表本次 上次 这次的error error[0]上上次  error[1]上次   error[2]本次
     * BL=[0] FL=[1] FR=[2] BR=[3]
     */

    if(flag)
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<3;j++)
            {
                Wheel_Speed_Error[i][j]=0;
            }
        }
       Wheel_Speed.BL_Speed=0;
       Wheel_Speed.FL_Speed=0;
       Wheel_Speed.BR_Speed=0;
       Wheel_Speed.FR_Speed=0;
    }flag=0;

    PID_Parameter Wheel_PID;
        //PID参数赋值
    Wheel_PID.Kp=0.409267124576902*4;
    Wheel_PID.Ki=0.0208088878485*4;
    Wheel_PID.Kd=-0.01851624170342353*4;

    //计算Error
    for(i=0;i<4;i++)
    {
        for(j=0;j<2;j++)
        {
          Wheel_Speed_Error[i][j]= Wheel_Speed_Error[i][j+1]; //误差传递
        }
        Wheel_Speed_Error[i][2]=*((float*)&(Wheel_Speed_Reference->BL_RPM)+i)-*(Measured_Wheel_RPM+i);
        //赋予当前误差 *((float*)&(Wheel_Speed_Reference->BL_RPM)+1)转为float数据依次访问
    }


    Wheel_PID_Controller(&Wheel_PID,Wheel_Speed_Error,Output,400,-400);

    Wheel_Speed.FR_Speed=Output[2];
    Wheel_Speed.BR_Speed=Output[3];
    Wheel_Speed.BL_Speed=Output[0];
    Wheel_Speed.FL_Speed=Output[1];

   //传值给Wheel
   SetMotor_Speed(&Wheel_Speed);


}



