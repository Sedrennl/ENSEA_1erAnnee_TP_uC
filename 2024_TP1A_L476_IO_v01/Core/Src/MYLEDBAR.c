/*
 * MYLEDBAR.c
 *
 *  Created on: Mar 26, 2024
 *      Author: sedre
 */

#include "MYLEDBAR.h"
#include "stm32l4xx.h"
#include "gpio.h"


//void MYLEDBAR_Init(){
//    GPIO_InitTypeDef GPIO_InitStruct;
//
//    // Activer le périphérique RCC pour le port GPIO utilisé
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//
//    // Configurer la broche associée au signal DI
//    GPIO_InitStruct.Pin = GPIO_PIN_0;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Configurer la broche en mode Push-Pull
//    GPIO_InitStruct.Pull = GPIO_NOPULL; // Désactiver la résistance de tirage
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Configurer la vitesse de la GPIO en haute fréquence
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialiser la broche GPIO pour DI
//
//    // Configurer la broche associée au signal DCKI
//    GPIO_InitStruct.Pin = GPIO_PIN_1;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialiser la broche GPIO pour DCKI
//}

void MYLEDBAR_DelayN(int N){
	//to wait a little in a simple loop:
	for(int n=N;n>=0;n--);
}


void MYLEDBAR_Delay1us() {
	//to wait a little more than 1 µs. It has not tobe accurate.
	MYLEDBAR_DelayN(sysTickInuS);
}

void MYLEDBAR_DelayNus(int N){
	//to wait a little more than N µs by calling N times the previous function.
	MYLEDBAR_Delay1us(N);

}

void MYLEDBAR_CLK_write(int val){
	//to write a 1 or 0 (LSB of val) on DCKI pin.
	HAL_GPIO_WritePin(DCKI_GPIO_Port, DCKI_Pin, val);
}

void MYLEDBAR_DI_write(int val){
	//to write a 1 or 0 (LSB of val) on DI pin.
	HAL_GPIO_WritePin(DI_GPIO_Port, DI_Pin, val);
}

void MYLEDBAR_LatchData(){
	MYLEDBAR_DelayNus(100);
	HAL_GPIO_TogglePin(DCKI_GPIO_Port, DCKI_Pin);
	MYLEDBAR_DelayNus(100);
}
void MYLEDBAR_Send8bits(int data){
    int mask = 0x01; // Masque pour extraire chaque bit de données

    // Envoyer les 8 bits de données
    for(int i = 0; i < 8; i++) {
        // Écrire le bit de données actuel sur la broche DI
       	MYLEDBAR_DI_write(data & mask);

        // Latch the data on the rising edge of DCKI
        MYLEDBAR_LatchData();

        // Décaler le masque pour passer au bit de données suivant
        mask >>= 1;
    }
}
void MYLEDBAR_Send16bits(int data){
	//to generate the DI and DCKI signals to send the 16 LSBs of data (because you will have to send 16-bit values
	//even if you use 8-bit values).
	MYLEDBAR_Send8bits(data & 0xFF);
	MYLEDBAR_Send8bits((data >> 8) & 0xFF);
}

void MYLEDBAR_SendLEDs() {
	int led[12]={0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00};
	for(int i = 12; i==0; i--){
		MYLEDBAR_Send16bits(led[i]);
	}

}
void MYLEDBAR_DispLED(int n, int val){
	//to light LED #n if val is1.
}


