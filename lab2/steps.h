#ifndef _STEPS_H_
#define _STEPS_H_

#include "main.h"

void step2();
void step3();
void step4();
void step5();

Server_Ptr get_link_from_id(Simulation_Run_Data_Ptr, int);
Fifoqueue_Ptr get_buffer_from_id(Simulation_Run_Data_Ptr, int);
int get_next_link(Simulation_Run_Data_Ptr);
#endif