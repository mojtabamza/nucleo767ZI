/*
 * communication.cpp
 *
 *  Created on: 20240909
 *      Author: Mojtaba.zamani
 */

#include "communication.hpp"



extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;



Communication_t::Communication_t(void) {
	this->newMsgFlag = false;
	this->RxIndex = 0;
	this->init();
}
void Communication_t::init(void) {
	HAL_UART_Receive_DMA(&huart3, this->buff, 1); // Start receiving data
}

Communication_t* Communication_t::getInstance(void) {
	static Communication_t* instance = nullptr;
	if(instance == nullptr)
		instance = new Communication_t();
	return instance;
}

void Communication_t::task(void) {
	//HAL_UART_Transmit(&huart3, (uint8_t*)("Task\r\n"), sizeof("Task\r\n"), 10);
	//HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	//refreshCommunication();

}

uint8_t* Communication_t::getMessage(void) {
	return this->buff;
}


bool Communication_t::newMessage(void) {
	return this->newMsgFlag;
}

void Communication_t::refreshCommunication(void) {
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	Communication_t* comm = Communication_t::getInstance();
    static uint8_t receivedMsg[MESSAGE_LEN];
    static uint32_t lastTick = HAL_GetTick();

    if(comm->RxIndex == 0) { //for handling wrong messages I put timeout. if it is a new message then update lastTick
    	lastTick = HAL_GetTick();
    }

    //if characters after the first character receive later than 1ms it means it's a new message and the previous characters are invalid
    //(baudrate = 115200 -> time to receive is 0.078 ms ## baudrate = 9600 -> time to receive is 0.9 ms)

    if((HAL_GetTick() - lastTick > 1) && comm->RxIndex > 0) {
    	memset(receivedMsg, 0, MESSAGE_LEN);
    	comm->RxIndex = 0;
    	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    	//return;
    }

    //receivedMsg[rx_index++] = huart3.pRxBuffPtr[0];
    if((receivedMsg[comm->RxIndex++] = huart3.pRxBuffPtr[0]) == 0) {
    	memset(receivedMsg, 0, MESSAGE_LEN);
    	comm->RxIndex = 0;
    }


    if (comm->RxIndex >= MESSAGE_LEN) {
        memcpy(comm->buff, receivedMsg, MESSAGE_LEN);
        comm->newMsgFlag = true;

        //HAL_UART_Transmit(&huart3, comm->buff, MESSAGE_LEN, 10);
        memset(receivedMsg, 0, MESSAGE_LEN);
        comm->RxIndex = 0;
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    }

    HAL_UART_Receive_DMA(&huart3, receivedMsg + comm->RxIndex, 1);
    lastTick = HAL_GetTick();
}