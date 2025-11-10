#include <eadk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "App";
const uint32_t eadk_api_level  __attribute__((section(".rodata.eadk_api_level"))) = 0;

void move_pointer() {
  while (true) {
    eadk_keyboard_state_t keyboard = eadk_keyboard_scan();
    if (eadk_keyboard_key_down(keyboard, eadk_key_back)) {
      return;
    }
}

int main(int argc, char * argv[]) {
  eadk_display_draw_string("Hello, world!", (eadk_point_t){0, 0}, true, eadk_color_black, eadk_color_white);
  move_pointer();
}
