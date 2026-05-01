#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include "sys/log.h"
#include <string.h>

#define LOG_MODULE "Flood-Sink"
#define LOG_LEVEL LOG_LEVEL_INFO

static int max_flood_level = 0;

/* Callback function when a packet is received */
void input_callback(const void *data, uint16_t len, const linkaddr_t *src, const linkaddr_t *dest) {
  if(len == sizeof(int)) {
    int received_val;
    memcpy(&received_val, data, sizeof(int));
    LOG_INFO("Received Alert from Node %d.%d: %d cm\n", src->u8[0], src->u8[1], received_val);

    // --- DATA AGGREGATION LOGIC ---
    if(received_val > max_flood_level) {
        max_flood_level = received_val;
        LOG_INFO(">>> NEW AGGREGATED MAX: %d cm <<<\n", max_flood_level);
    }
  }
}

PROCESS(sink_process, "Flood Sink Node");
AUTOSTART_PROCESSES(&sink_process);

PROCESS_THREAD(sink_process, ev, data) {
  PROCESS_BEGIN();

  nullnet_set_input_callback(input_callback);
  LOG_INFO("Sink Node Started. Waiting for Alerts...\n");

  PROCESS_END();
}
