/*
 * logic.h
 *
 *  Created on: Mar 7, 2025
 *      Author: Krzysztof Tomicki
 */

#ifndef INC_LOGIC_H_
#define INC_LOGIC_H_
typedef enum {
	STATE_INIT,
	STATE_REG_TYPE,
	STATE_BANG_BANG_CONF,
	STATE_PID_CONF
}SystemState;

void state_machine_run(void); //main loop for state machine
void change_state(SystemState newState); //move between states in a state machine

#endif /* INC_LOGIC_H_ */
