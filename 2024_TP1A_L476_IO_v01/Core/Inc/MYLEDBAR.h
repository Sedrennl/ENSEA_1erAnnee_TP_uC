/*
 * MYLEDBAR.h
 *
 *  Created on: Mar 26, 2024
 *      Author: sedre
 */

#ifndef INC_MYLEDBAR_H_
#define INC_MYLEDBAR_H_

#define sysTickInuS 80

void MYLEDBAR_Init() ;

void MYLEDBAR_DelayN(int N);


void MYLEDBAR_Delay1us() ;

void MYLEDBAR_DelayNus(int N);

void MYLEDBAR_CLK_write(int val);
void MYLEDBAR_DI_write(int val);

void MYLEDBAR_LatchData();
void MYLEDBAR_Send8bits(int data);
void MYLEDBAR_Send16bits(int data);
void MYLEDBAR_SendLEDs() ;
void MYLEDBAR_DispLED(int n, int val);

#endif /* INC_MYLEDBAR_H_ */
