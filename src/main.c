#include <eadk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LCD_REG (*((volatile unsigned short *) 0x60000000))
#define LCD_DATA (*((volatile unsigned short *) (0x60000000 | (1<<(16+1))) ))

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "App";
const uint32_t eadk_api_level  __attribute__((section(".rodata.eadk_api_level"))) = 0;

void move_pointer() {
  while (true) {
    eadk_keyboard_state_t keyboard = eadk_keyboard_scan();
    if (eadk_keyboard_key_down(keyboard, eadk_key_back)) {
      return;
    }
  }
}

static inline void send_command(uint8_t c) {
    LCD_REG = c;
}
static inline uint16_t receive_data() {
    return LCD_DATA;
}

void read_id(uint8_t id[3]) {
    send_command(0x04);
    receive_data(); // Dummy read, per datasheet
    id[0] = receive_data();
    id[1] = receive_data();
    id[2] = receive_data();
}

int main(int argc, char * argv[]) {
  uint8_t id[3];
  char msg[30];
  read_id(id);
  sprintf(msg, "id=0x%02X%02X%02X\r\n", id[0], id[1], id[2]);
  eadk_display_draw_string(msg, (eadk_point_t){0, 0}, true, eadk_color_black, eadk_color_white);
  move_pointer();
}
