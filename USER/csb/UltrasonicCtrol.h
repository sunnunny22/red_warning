#ifndef __ULTRASONICCTROL_H_
#define __ULTRASONICCTROL_H_

extern volatile unsigned int distance_cm;//��ǰ����
void UltraSoundInit(void);
void GetDistanceDelay(void);
void LCD12864WriteDistance(unsigned int distance);
#endif
