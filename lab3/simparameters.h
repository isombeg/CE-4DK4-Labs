
/*
 * 
 * Call Blocking in Circuit Switched Networks
 * 
 * Copyright (C) 2014 Terence D. Todd
 * Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/*******************************************************************************/
<<<<<<< HEAD

#define Call_ARRIVALRATE 0.2/* calls/minute */
#define MEAN_CALL_DURATION 1 /* minutes */
#define RUNLENGTH 5e6 //5e6 /* number of successful calls */
=======
// TODO: Change everywhere this is referenced
#define Call_ARRIVALRATE 0.3   /* calls/minute */
#define MEAN_CALL_DURATION 1 /* minutes */
#define RUNLENGTH 5e6 /* number of successful calls */
>>>>>>> origin/master
#define BLIPRATE 1e3
#define NUMBER_OF_CHANNELS 2
#define W 1 // mean time to hang up in minutes
#define T_SEC 0.5 // in minutes

/* Comma separated list of random seeds to run. */
<<<<<<< HEAD
#define RANDOM_SEED_LIST 400137394, 400182022, 400184894
=======
#define RANDOM_SEED_LIST 333, 4444, 55555, 400137394
>>>>>>> origin/master

/*******************************************************************************/

#endif /* simparameters.h */




