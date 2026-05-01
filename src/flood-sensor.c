
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include "contiki.h"
#include "sys/log.h"
#include <stdio.h>
#include <stdlib.h>

#define LOG_MODULE "Flood-Node"
#define LOG_LEVEL LOG_LEVEL_INFO

static int HT = 30;         // Hard Threshold: 30cm
static int ST = 2;          // Soft Threshold: 2cm
static int last_sent = 0;

PROCESS(flood_process, "Flood Node");
AUTOSTART_PROCESSES(&flood_process);

PROCESS_THREAD(flood_process, ev, data) {
  static struct etimer timer;
  PROCESS_BEGIN();
  etimer_set(&timer, CLOCK_SECOND * 5);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    // Simulate water level (Random 0-50)
    int current_level = rand() % 50;

    // TEEN Reactive Logic
    if(current_level > HT) {
      if(abs(current_level - last_sent) >= ST) {
        LOG_INFO("!!! ALERT: Water at %d cm. Transmitting to Sink...\n", current_level);
	nullnet_buf = (uint8_t *)&current_level;
	nullnet_len = sizeof(int);
	NETSTACK_NETWORK.output(NULL); // Broadcast the alert
	last_sent = current_level;
      }
    } else {
        LOG_INFO("Normal: %d cm\n", current_level);
    }
    etimer_reset(&timer);
  }
  PROCESS_END();
}
