#include <console.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <timer.h>
#include <unistd.h>

static void walk_region(uint8_t *start, uint8_t *end) {
  uint8_t *curr;
  uint8_t sum = 0;

  printf("Region start: %X\n", (size_t)start);
  printf("Region end: %X\n\n", (size_t)end);

  delay_ms(2000);

  // Walk over region
  for (curr = start; curr < end; curr++) {
    sum ^= *curr;
    // Print message every 1024 bytes 
    if ((curr - start) % 1024 == 0) {
      printf("Reached address %X\n", (size_t)curr);
      delay_ms(500);
    }
  }

  printf("Sum: %X\n\n", sum);
}

int main(void) {
  uint8_t *flash_start  = tock_app_flash_begins_at();
  uint8_t *flash_end    = tock_app_flash_ends_at();
  uint8_t *memory_start = tock_app_memory_begins_at();
  uint8_t *memory_end   = tock_app_memory_ends_at();

  printf("\n[TEST] MPU Print\n");

  printf("This test tests that a process can access all of its memory.\n");
  printf("It walks over the process flash and memory regions and prints\n");
  printf("the 8-bit XOR sum of each region.\n\n");

  // Flash

  printf("Flash Walk\n\n");

  walk_region(flash_start, flash_end);

  // Memory

  printf("Memory Walk\n\n");

  walk_region(memory_start, memory_end);

  printf("Done.\n");
}
