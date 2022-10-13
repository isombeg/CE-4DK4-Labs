
/*
 * 
 * Simulation of A Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/******************************************************************************/

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/******************************************************************************/

#define PACKET_ARRIVAL_RATE 700 /* packets per second */
#define PACKET_ARRIVAL_RATE_2_3 = 500 

#define PACKET_LENGTH 1000 /* bits */

#define LINK_BIT_RATE 2e6 /* bits per second */
#define LINK_BIT_RATE_2_3 1e6

#define RUNLENGTH 10e6 /* packets */

#define STUDENT_NUMBER_GJ 400137394
#define STUDENT_NUMBER_CARLOS 400184894
#define STUDENT_NUMBER_RAFI 400182022


/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 333333, 444444, STUDENT_NUMBER_GJ, STUDENT_NUMBER_CARLOS, STUDENT_NUMBER_RAFI, 336533, 293343, 183233, 523033, 734392

#define PACKET_XMT_TIME ((double) PACKET_LENGTH/LINK_BIT_RATE)
#define PACKET_XMT_TIME_2_3 ((double) PACKET_LENGTH/LINK_BIT_RATE_2_3)

#define BLIPRATE (RUNLENGTH/1000)

/******************************************************************************/

#endif /* simparameters.h */



