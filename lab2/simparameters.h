
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


// Data traffic step 6
#define PACKET_ARRIVAL_RATE 21/* packets per second*/
#define PACKET_LENGTH 40e3 /* bits */

// Voice traffic step 6
#define VOICE_PACKET_ARRIVAL_RATE 50/* packets per second*/
#define VOICE_PACKET_LENGTH 1776 /* bits */

#define LINK_BIT_RATE 1e6 /* bits per second */
#define RUNLENGTH 10e6 /* packets - default is 10e6*/ 

#define STUDENT_NUMBER_GJ 400137394
#define STUDENT_NUMBER_CARLOS 400184894
#define STUDENT_NUMBER_RAFI 400182022


/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 333333, 444444, STUDENT_NUMBER_GJ, STUDENT_NUMBER_CARLOS, STUDENT_NUMBER_RAFI, 555555, 666666, 777777, 888888, 999999

#define PACKET_XMT_TIME ((double) PACKET_LENGTH/LINK_BIT_RATE)
#define VOICE_PACKET_XMT_TIME ((double) VOICE_PACKET_LENGTH/LINK_BIT_RATE) // Step 6

#define BLIPRATE (RUNLENGTH/1000)

/******************************************************************************/

#endif /* simparameters.h */



