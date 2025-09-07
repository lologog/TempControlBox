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
	STATE_CONTROL_TYPE,
	STATE_ON_OFF_TEMP_CONF,
	STATE_PID_TEMP_CONF
}SystemState;

#endif /* INC_LOGIC_H_ */
