#include <stdbool.h>
#include <stdio.h>

#include <led.h>
#include <radio.h>
#include <timer.h>

#define BUF_SIZE 60
char packet_rx[BUF_SIZE];
char packet_tx[BUF_SIZE];
bool toggle = true;

static void callback(__attribute__ ((unused)) int err,
                     __attribute__ ((unused)) int payload_length,
                     __attribute__ ((unused)) int unused2,
                     __attribute__ ((unused)) void* ud) {
  led_toggle(0);
  radio_receive_callback(callback, packet_rx, BUF_SIZE);
}

int main(void) {
  int i;
  // printf("Starting 802.15.4 packet reception app.\n");
  for (i = 0; i < BUF_SIZE; i++) {
    packet_rx[i] = 0;
    packet_tx[i] = i;
  }
  radio_set_addr(0x802);
  radio_set_pan(0xABCD);
  radio_commit();
  radio_init();
  radio_receive_callback(callback, packet_rx, BUF_SIZE);
  while (1) {
    delay_ms(4000);
  }
}