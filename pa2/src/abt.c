#include "../include/simulator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//Brecken McGeough
//breckenm
//50301442



int ind; //index of currently buffered packet, to keep adding necessary buffered packets to the end of the buffer
int count; //index of the packet that is currently being unbuffered and sent to B when previous packet is successfully acked
struct pkt packet_buffer[1000]; //stores buffered packets
struct pkt current_packet; //the packetly currently being sent and waiting for successfully ack from 

int in_progress; //if a packet is currently being sent and waiting for successful ack from B
int timer_started; //if the timer is started

int seqnum;
int expected_seqnum; //the expected seqnum for the packet sent to B

int resent; //if the packet was resent to B after timeout/unsuccessful ack to A



//use standard checksum algorithm
int checksum(struct pkt packet){
  char terminated_payload[21];
  memset(terminated_payload, 0, 21);
  memcpy(terminated_payload, packet.payload, 20);
  //printf("\n%s\n", terminated_payload);

  uint16_t sum = 0;
  for (int i = 0; i < strlen(terminated_payload)-1; i += 2){
    sum += (terminated_payload[i] << 8) | terminated_payload[i+1]; //shift first letter over 8 bits (since its 1 byte=8 bits) so it takes up second 8 bits, then bitwise OR
    //with second letter so that it takes up first 8 bits, ex. (two letters, 00101010, 00101011: 00101010<<8=001010100000000, 0010101000000000|0000000000101011=0010101000101011
  }

  sum += (uint16_t)packet.seqnum; //can cast to 16 bit even though these are 32 bit ints cause packet.seqnum is 0 or 1 32 bit, so no fear of data loss since only use first bit
  sum += (uint16_t)packet.acknum;

  return ~sum; //take 1's complement of the sum

}


void A_output(message)
  struct msg message;
{
  printf("A received message from layer5%s\n", message.data);
  struct pkt packet;
  memset(packet.payload, 0, 20);

  memcpy(packet.payload, message.data, 20);

  packet.seqnum = seqnum;
  packet.acknum = 0;
  packet.checksum = checksum(packet);

  seqnum = 1 - seqnum; //alternate bit

  if (in_progress == 0){ //if not currently waiting for ack from a packet
    in_progress = 1; 
    timer_started = 1;
    current_packet = packet;

    printf("\npacket sent from A to B: %s\n", packet.payload);

    starttimer(0, 20);
    tolayer3(0, packet);
  }else{
    printf("\nbuffered packet: %s\n", packet.payload);
    packet_buffer[ind] = packet;
    ind++;
  }
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(packet)
  struct pkt packet;
{ 

  if(timer_started == 1){
    printf("\nstopped timer at A\n");
    stoptimer(0);
    timer_started = 0;
  }
  if (packet.acknum == 1 && checksum(packet) == packet.checksum){ 
    printf("\nrecieved ACK\n");
    printf("%s\n", packet.payload);

    in_progress = 0;

    if (resent == 1){
      resent = 0;
    }

    if (count < ind){
      printf("unbuffering packet: %s\n", packet_buffer[count].payload);
      in_progress = 1;
      current_packet = packet_buffer[count];
      count++;
      printf("sending buffered packet to B and starting timer\n");
      A_timerinterrupt();
    }

  }else{
    printf("\ndid not receive ACK\n");
    resent = 1;
    A_timerinterrupt();
  }

}

/* called when A's timer goes off */
void A_timerinterrupt()
{
  printf("\ntimed out, starting timer and sending to B again\n");
  timer_started = 1;
  starttimer(0, 20);
  tolayer3(0, current_packet);
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
  seqnum = 0;
  timer_started = 0;
  in_progress = 0;
  ind = 0;
  count = 0;
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(packet)
  struct pkt packet;
{
  printf("received packet: %s\n", packet.payload);
  if (packet.checksum != checksum(packet) || packet.seqnum != expected_seqnum){
    printf("\nchecksum mismatch or seqnum != expected, allowing timer to expire\n");
  }else{
    
    packet.acknum = 1;
    packet.checksum = checksum(packet);

    printf("send ACK to A for packet:%s\n", packet.payload);
    
    if (resent == 0){ //only do if packet is not a resent packet
      expected_seqnum = 1 - expected_seqnum;
      tolayer5(1, packet.payload);
    }

    tolayer3(1, packet);
  }
}

/* the following routine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
  expected_seqnum = 0;
  resent = 0;
}

