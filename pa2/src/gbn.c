#include "../include/simulator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//Brecken McGeough
//breckenm
//50301442

struct pkt packet_buffer[5000]; //stores buffered packets


int N;
int base;
int next_seqnum;
int expected_seqnum;
struct pkt prev_packet;


int ind;



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

/* called from layer 5, passed the data to be sent to other side */
void A_output(message)
  struct msg message;
{
  struct pkt packet;
  memcpy(packet.payload, message.data, 20);
  packet.seqnum = ind;
  packet.acknum = 0;
  packet.checksum = checksum(packet);

  packet_buffer[ind] = packet;
  printf("storing packet: %s\n", packet.payload);
  ind++; //index to keep track of next index in packet_buffer array to store packet
  printf("next_seqnum: %d\n", next_seqnum);
  printf("base: %d\n", base);
  printf("N: %d\n", N);
  if (next_seqnum < base+N){
    printf("sending packet: %s\n", packet.payload);
    tolayer3(0, packet_buffer[next_seqnum]);
    if (base == next_seqnum){
      starttimer(0, 20);
    }
    next_seqnum++;
  }
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(packet)
  struct pkt packet;
{
  printf("received ACK for packet: %s\n", packet.payload);
  if (packet.checksum == checksum(packet)){
    printf("ACK checksum matches\n");
    base = packet.acknum + 1;
    if (base == next_seqnum){
      stoptimer(0);
    }
  }
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
  printf("timer expired\n");
  starttimer(0, 20);
  for (int i = base; i < next_seqnum; i++){
    tolayer3(0, packet_buffer[i]);
  }
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
  N = getwinsize();
  base = 0;
  next_seqnum = 0;

  ind = 0;

}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(packet)
  struct pkt packet;
{
  printf("received packet: %s\n", packet.payload);
  if (packet.checksum != checksum(packet) || packet.seqnum != expected_seqnum || (prev_packet.seqnum != packet.seqnum-1 && prev_packet.seqnum != -1)){
    printf("\nchecksum mismatch or seqnum != expected, allowing timer to expire\n");
    packet.acknum = prev_packet.seqnum;
    packet.checksum = checksum(packet); //resend packet if fails conditionals with previous successful packet seqnum
    tolayer3(1, packet);
  }else{
    
    prev_packet = packet;

    packet.acknum = expected_seqnum;
    packet.checksum = checksum(packet);

    printf("send ACK to A for packet:%s\n", packet.payload);
    
    tolayer5(1, packet.payload);

    expected_seqnum++;

    tolayer3(1, packet);
  } 
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
  expected_seqnum = 0;
  prev_packet.seqnum = -1;
}
