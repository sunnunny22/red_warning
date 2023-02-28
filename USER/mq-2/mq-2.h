#ifndef __MQ_2_H
#define __MQ_2_H

#include "sys.h"


#define MQ_2_READ_TIMES	10		//定义烟雾传感器读取次数,读这么多次,然后取平均值


void MQ_2_Configuration(void);


u32 Get_MQ_2_Value(void);        //返回烟雾浓度值

#endif
