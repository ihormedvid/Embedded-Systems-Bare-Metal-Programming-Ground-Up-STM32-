/*
 * tim.h
 *
 *  Created on: Jun 13, 2024
 *      Author: Ihor
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);


#define SR_UIF		(1<<0)

void tim2_1hz_interrupt_init(void);
#endif /* TIM_H_ */
