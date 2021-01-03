
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define _QWERTY 0
#define _QWERTY_1 1
#define _NAV 2
#define _NUM 4
#define _GAME 8

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case _QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case _QWERTY_1:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case _NUM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Num");
    break;
  case _NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Nav");
    break;
  case _GAME:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Game");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
