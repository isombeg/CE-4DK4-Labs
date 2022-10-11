
/*
 * 
 * Simulation_Run of A Single Server Queueing System
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

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/******************************************************************************/

/*
 * This function outputs a progress message to the screen to indicate this are
 * working.
 */

void
output_progress_msg_to_screen(Simulation_Run_Ptr simulation_run)
{
  double percentage_done;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter++;

  if((data->blip_counter >= BLIPRATE)
     ||
     (data->number_of_packets_processed >= RUNLENGTH)) {

    data->blip_counter = 0;

    percentage_done =
      100 * (double) data->number_of_packets_processed/RUNLENGTH;

    printf("%3.0f%% ", percentage_done);

    printf("Successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \r", 
	   data->number_of_packets_processed, data->arrival_count);

    fflush(stdout);
  }

}

/*
 * When a simulation_run run is completed, this function outputs various
 * collected statistics on the screen.
 */

void
output_results(Simulation_Run_Ptr simulation_run)
{
  double xmtted_fraction;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  printf("\n");
  printf("Random Seed = %d \n", data->random_seed);
  printf("Packet arrival count = %ld \n", data->arrival_count);

  xmtted_fraction = (double) data->number_of_packets_processed /
    data->arrival_count;

  printf("Transmitted packet count  = %ld (Service Fraction = %.5f)\n",
	 data->number_of_packets_processed, xmtted_fraction);

  printf("Arrival rate = %.3f packets/second \n", (double) PACKET_ARRIVAL_RATE);
  printf("Voice Arrival rate = %3.f packets/second \n", (double) VOICE_PACKET_ARRIVAL_RATE);

  printf("Mean Delay (msec) = %.2f \n",
	 1e3*data->accumulated_delay/data->number_of_packets_processed);

  // Step 6 change
   printf("Voice Packet Mean Delay (msec) = %.2f \n",
	 1e3*data->voice_accumulated_delay/data->number_of_packets_processed); 
   
  // printf("# of Packet's delay exceeding 20msec = %d \n", data->packet_delay_exceed_20);
  // printf("Probability of the # of Packet's delay exceeding 20msec = %0.10f \n", (((double)data->packet_delay_exceed_20)/(double)(data->number_of_packets_processed))*100);

  printf("\n");
}

// void
// write_to_csv(FILE* fpt, Simulation_Run_Data_Ptr data)
// {
//   double xmtted_fraction = (double) data->number_of_packets_processed /
//     data->arrival_count;

//   fprintf(
//     fpt,
//     "$u, %d, %d, %d, %f, %f, %d, %f",
//     data->random_seed,
//     data->arrival_count,
//     data->number_of_packets_processed,
//     xmtted_fraction,
//     // !: packet arrival rate
//     1e3*data->accumulated_delay/data->number_of_packets_processed,
//     data->packet_delay_exceed_20,
//     (data->packet_delay_exceed_20)/data->number_of_packets_processed
//   );
// }


