
#ifndef INC_PROCESS_HPP_
#define INC_PROCESS_HPP_

#include <vector>
#include "main.h"
#include <memory>
#include "communication.hpp"

using std::vector;

class Communication_t;

class Process_t {
public:
	Process_t(void);
	~Process_t();
	void task(void);
	bool checkForNewData(void);
	bool checkValidity(void);
	bool checkLength();
	bool checkStartBytes();
	bool checkEndBytes();
	bool parseData(void);
	bool checkDeviceID(void);
	bool checkPassword(void);
	void commandProcess(void);
private:
	Communication_t* communicationObj;
};




#endif /* INC_PROCESS_HPP_ */
