#include "debug.h"
#include "Filter.h"

float High_Pass_Filter(float Real_Time_ms,float Real_Time_s,float Signal,float Cuttoff_Frequency)
{
    double RC=1/(2*3.14*Cuttoff_Frequency);
    static double Signal_In[2]={0};//[0]上次时间 [1]本次时间
    static double Signal_Out[2]={0};//[0]上次时间 [1]本次时间
    static double Time_Record[2]={0}; //[0]上次时间 [1]本次时间
    double Time_Increment;

    Time_Record[0]=Time_Record[1]; //位移上次时间
    Time_Record[1]=Real_Time_ms+Real_Time_s*1000; //储存本次时间
    Time_Increment=Time_Record[1]-Time_Record[0];

    Signal_In[0]=Signal_In[1];
    Signal_In[1]=Signal;

    Signal_Out[0]=Signal_Out[1];

    Signal_Out[1]=(RC/(RC+Time_Increment))*(Signal_Out[0]+Signal_In[1]-Signal_In[0]);


    return Signal_Out[1];

}


float Low_Pass_Filter(float Real_Time_ms,float Real_Time_s,float Signal,float Cuttoff_Frequency)
{
    double RC=1/(2*3.14*Cuttoff_Frequency);
    static double Signal_In[2]={0};//[0]上次时间 [1]本次时间
    static double Signal_Out[2]={0};//[0]上次时间 [1]本次时间
    static double Time_Record[2]={0}; //[0]上次时间 [1]本次时间
    double Time_Increment;

    Time_Record[0]=Time_Record[1]; //位移上次时间
    Time_Record[1]=Real_Time_ms+Real_Time_s*1000; //储存本次时间
    Time_Increment=Time_Record[1]-Time_Record[0];

    Signal_In[0]=Signal_In[1];
    Signal_In[1]=Signal;

    Signal_Out[0]=Signal_Out[1];

    Signal_Out[1]=(RC/(RC+Time_Increment))*Signal_Out[0]+(Time_Increment/(RC+Time_Increment))*Signal_In[1];


    return Signal_Out[1];

}



