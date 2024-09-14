/*
 * communication.hpp
 *
 *  Created on: Nov 17, 2023
 *      Author: bvi499
 */

#ifndef INC_COMMUNICATION_HPP_
#define INC_COMMUNICATION_HPP_

#include "main.h"
#include "stm32f7xx_hal.h"

#include <string>
#include <vector>
#include <cstring>

using std::string;
using std::vector;

#define MSG_FORMAT "[!01AFRYFW010FW010FW010FW010!]"
#define MESSAGE_LEN		(sizeof(MSG_FORMAT) - 1)



class Communication_t {
public:
	static Communication_t* getInstance(void);
	void init(void);
	void task(void);
	void refreshCommunication(void);
	uint8_t* getMessage(void);
	uint8_t buff[MESSAGE_LEN];
	bool newMessage(void);
	bool newMsgFlag;
	uint8_t RxIndex;
private:
	Communication_t(void);


};


#endif /* INC_COMMUNICATION_HPP_ */