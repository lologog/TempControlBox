/*
 * logic.h
 *
 *  Created on: Mar 7, 2025
 *      Author: Krzysztof Tomicki
 */

#ifndef INC_LOGIC_H_
#define INC_LOGIC_H_

#include "main.h"
#include "lcd1602.h"
#include "keyboard.h"
#include <string.h>
#include <stdlib.h>

typedef enum {
	STATE_INIT,
	STATE_REG_TYPE,
	STATE_BANG_BANG_TEMP_CONF,
	STATE_BANG_BANG_OFFSET_CONF,
	STATE_PID_CONF
}SystemState;

void state_machine_run(void); // main loop for state machine
void change_state(SystemState newState); // move between states in a state machine

// State handlers
void state_init(void);
void state_reg_type(void);
void state_bang_bang_temp_conf(void);
void state_bang_bang_offset_conf(void);

#endif /* INC_LOGIC_H_ */
