// TaskManager.h

#ifndef _TASKMANAGER_h
#define _TASKMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Definitions.h"
#include "ActionChain.h"

class ActionChain;

class TaskManager {
public:
	uint8_t task_ptr;
	Action *queue[TASKBUFFER][PARALLELTASKS];
	uint8_t getNextPosition(uint8_t delay);
	uint8_t getNextPositionFrom(uint8_t current_pos, uint8_t delay);
	uint8_t getOffSet(ActionChain *actionchain);

	TaskManager();
	void next();
	void prev();

	void addActions(ActionChain *actionchain);
	void execute();
};
#endif