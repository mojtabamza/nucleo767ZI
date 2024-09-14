
#include "process.hpp"
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;

Process_t::Process_t(void) {
	this->communicationObj = Communication_t::getInstance();
}


Process_t::~Process_t() {
}


void Process_t::task(void) {
	if(checkForNewData()) {
		if(checkValidity()) {
			if(parseData()) {
				if(checkDeviceID()) {
					if(checkPassword()) {
						commandProcess();
					}
				}
			}
		}
	}
}

bool Process_t::checkForNewData(void) {
	if(communicationObj->newMsgFlag) {
		communicationObj->newMsgFlag = false;
		return true;
	}
	return false;
}

bool Process_t::checkValidity(void) {
    return true;
}

bool Process_t::checkLength(void) {
    return true;
}

bool Process_t::checkStartBytes(void) {
    return true;
}

bool Process_t::checkEndBytes(void) {
	return true;
}


bool Process_t::parseData(void) {
	//const char* receivedData = (char*)this->communicationObj->buff;   //"[!01AFRYFW010FW010FW010FW010!]"

	return true;
}
bool Process_t::checkDeviceID(void) {
    return true;
}
bool Process_t::checkPassword(void) {
    return true;
}
void Process_t::commandProcess(void) {
    const char* receivedData = (char*)this->communicationObj->buff;   //"[!01AFRYFW010FW010FW010FW010!]"
    HAL_UART_Transmit(&huart3, (uint8_t*)receivedData, strlen(receivedData), 10);
	
}
