// systemctl stop ModemManager.service

#include QMK_KEYBOARD_H

#define SENDSTRING_MM1 ""
#define SENDSTRING_MM2 ""
#define SENDSTRING_MM3 ""

#include "secrets.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;
uint8_t ENCODER_MODE = 0;

enum custom_keycodes {
  T_ENC_MOD
};

#define _QWERTY 0
#define _NAV 1
#define _NUM 2
#define _GAME 3

enum {
  TD_SCLN_MIN
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for ;, twice for -
  [TD_SCLN_MIN] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_MINUS)
};

// Combo definitions
enum combos {
  // ONETWO_SEVEN,
  // TWOTHREE_EIGHT,
  // THREEFOUR_NINE,
  JK_MIDDLE,
  // FOURFIVE_F12,
  // SIXSEVEN_F2
};

// const uint16_t PROGMEM onetwo_combo[] = {KC_1, KC_2, COMBO_END};
// const uint16_t PROGMEM twothree_combo[] = {KC_2, KC_3, COMBO_END};
// const uint16_t PROGMEM threefour_combo[] = {KC_3, KC_4, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM fourfive_combo[] = {KC_4, KC_5, COMBO_END};
// const uint16_t PROGMEM sixseven_combo[] = {KC_6, KC_7, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  // [ONETWO_SEVEN] = COMBO(onetwo_combo, KC_7),
  // [TWOTHREE_EIGHT] = COMBO(twothree_combo, KC_8),
  // [THREEFOUR_NINE] = COMBO(threefour_combo, KC_9),
  [JK_MIDDLE] = COMBO(jk_combo, KC_MS_BTN3),
  // [FOURFIVE_F12] = COMBO(fourfive_combo, KC_F12),
  // [SIXSEVEN_F2] = COMBO(sixseven_combo, KC_F2)
};

// Lily Work
// KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,KC_APP ,T_ENC_MOD, KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_SCLN_MIN),  KC_RSFT,
// Lily Home
// KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,TO(_GAME),T_ENC_MOD, KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_SCLN_MIN),  KC_RSFT,


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LEAD, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    RGUI_T(KC_QUOT), KC_RCTL, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,KC_APP ,T_ENC_MOD, KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_SCLN_MIN),  KC_RSFT, \
                          KC_UNDS, KC_LGUI,    KC_BSPC, KC_DEL,   LT(_NUM, KC_ENT),   LT(_NAV, KC_SPC),   KC_LALT, KC_MINUS \
),
[_NAV] = LAYOUT( \
  _______, KC_DEL ,KC_INSERT,KC_PAUSE,KC_CALC, KC_MYCM,                  _______, _______, _______, _______, _______, _______,\
  _______, KC_GRV , KC_DLR , KC_EXLM, KC_LCBR, KC_RCBR,                   KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______ , _______, \
  _______, KC_DQUO, KC_HASH, KC_AMPR, KC_LPRN, KC_RPRN,                   KC_LEFT, KC_DOWN,  KC_UP ,KC_RIGHT, KC_MS_WH_UP, KC_MS_WH_LEFT, \
  _______, KC_MINS, KC_UNDS, KC_PIPE, KC_LBRC, KC_RBRC, _______, _______, LCTL(KC_Z), LCTL(KC_C), LCTL(KC_V), LALT(KC_LEFT), KC_MS_WH_DOWN, KC_MS_WH_RIGHT, \
                             _______, _______, KC_LSFT, _______, _______, _______, _______, _______\
),
[_NUM] = LAYOUT( \
  _______, _______, KC_F10, KC_F11, KC_F12, _______,                   _______, _______, _______, _______, KC_PAST, KC_PSLS,\
  _______, _______,  KC_F7,  KC_F8,  KC_F9, _______,                   _______,   KC_P7,   KC_P8,   KC_P9, KC_PMNS, _______, \
  _______, _______,  KC_F4,  KC_F5,  KC_F6, _______,                    KC_EQL,   KC_P4,   KC_P5,   KC_P6, KC_PPLS, _______, \
  _______, _______,  KC_F1,  KC_F2,  KC_F3, _______, _______, _______, KC_MINS,   KC_P1,   KC_P2,   KC_P3, KC_PENT, _______, \
                             _______, _______, _______, _______, KC_DOT , KC_COMM,KC_P0, _______\
),
[_GAME] = LAYOUT( \
TO(_QWERTY), _______, _______, _______, _______, _______,                   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,\
    _______, KC_U   , KC_I   , KC_O   , KC_P   , _______,                   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , \
    _______, KC_J   , KC_K   , KC_L   , KC_N   , _______,                   KC_M   , KC_A   , KC_S   , KC_D   , KC_F   , KC_G, \
    _______, _______, _______, _______, KC_F1  , KC_F2  , KC_F3  , KC_ESC , KC_H   , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B, \
                               _______, KC_P   , KC_TAB , KC_M   , KC_SPC , KC_LSFT, KC_LCTRL, KC_LALT\
),
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    // oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    // set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case T_ENC_MOD:
      if (record->event.pressed) {
        if (ENCODER_MODE >= 2) {
          ENCODER_MODE = 0;
        } else {
          ENCODER_MODE++;
        }
      } else {
        // when keycode QMKBEST is released
      }
      break;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (ENCODER_MODE == 0) {
    if (clockwise) {
      register_code(KC_LSFT);
      tap_code(KC_LEFT);
      unregister_code(KC_LSFT);
    } else {
      register_code(KC_LSFT);
      tap_code(KC_RIGHT);
      unregister_code(KC_LSFT);
    }
  } else if (ENCODER_MODE == 1) {
    if (clockwise) {
      tap_code(KC_MS_WH_UP);
    } else {
      tap_code(KC_MS_WH_DOWN);
    }
  } else if (ENCODER_MODE == 2) {
    if (clockwise) {
      register_code(KC_LSFT);
      register_code(KC_LCTRL);
      tap_code(KC_TAB);
      unregister_code(KC_LCTRL);
      unregister_code(KC_LSFT);
    } else {
      register_code(KC_LCTRL);
      tap_code(KC_TAB);
      unregister_code(KC_LCTRL);
    }
  }
}

LEADER_EXTERNS();
bool did_leader_succeed;
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;
    SEQ_ONE_KEY(KC_T) {
        // new tab
        SEND_STRING(SS_LCTRL("t"));
        did_leader_succeed = true;
    }

    SEQ_TWO_KEYS(KC_T, KC_T) {
        // reopen tab
        SEND_STRING(SS_LCTRL(SS_LSFT("t")));
        did_leader_succeed = true;
    }
    
    SEQ_TWO_KEYS(KC_ESC, KC_ESC) {
        // alt + f4
        register_code(KC_LALT);
        tap_code(KC_F4);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_TAB) {
        // double space
        SEND_STRING("  ");
        did_leader_succeed = true;
    }

    SEQ_TWO_KEYS(KC_TAB, KC_TAB) {
        // quad space
        SEND_STRING("    ");
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_F) {
        // next tab
        register_code(KC_LCTL);
        tap_code(KC_TAB);
        unregister_code(KC_LCTL);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_D) {
        // prev tab
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_TAB);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_M) {
        // open mail + refresh
        register_code(KC_LGUI);
        tap_code(KC_3);
        unregister_code(KC_LGUI);
        tap_code(KC_F9);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_H) {
        // virtual Desktop left
        register_code(KC_LGUI);
        register_code(KC_LCTL);
        tap_code(KC_LEFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LGUI);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_L) {
        // virtual Desktop right
        register_code(KC_LGUI);
        register_code(KC_LCTL);
        tap_code(KC_RIGHT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LGUI);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_J) {
        // copy down
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_DOWN);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_K) {
        // copy up
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code(KC_UP);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_SLSH) {
        // backslash
        tap_code(KC_BSLASH);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_LSFT) {
        // Capslock
        tap_code(KC_CAPSLOCK);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_RCTL) {
        // Refresh
        tap_code(KC_F5);
        did_leader_succeed = true;
    }

    SEQ_TWO_KEYS(KC_RCTL, KC_RCTL) {
        // CTRL + Refresh
        register_code(KC_LCTL);
        tap_code(KC_F5);
        unregister_code(KC_LCTL);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_E) {
        // €
        register_code(KC_LALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_1);
        tap_code(KC_KP_2);
        tap_code(KC_KP_8);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_S) {
        // ß
        register_code(KC_LALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_2);
        tap_code(KC_KP_2);
        tap_code(KC_KP_3);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }
    
    SEQ_ONE_KEY(KC_A) {
        // ä
        register_code(KC_LALT);
        tap_code(KC_KP_1);
        tap_code(KC_KP_3);
        tap_code(KC_KP_2);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_TWO_KEYS(KC_A, KC_A) {
        // Ä
        register_code(KC_LALT);
        tap_code(KC_KP_1);
        tap_code(KC_KP_4);
        tap_code(KC_KP_2);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_U) {
        // ü
        register_code(KC_LALT);
        tap_code(KC_KP_1);
        tap_code(KC_KP_2);
        tap_code(KC_KP_9);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_TWO_KEYS(KC_U, KC_U) {
        // Ü
        register_code(KC_LALT);
        tap_code(KC_KP_1);
        tap_code(KC_KP_5);
        tap_code(KC_KP_4);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_O) {
        // ö
        register_code(KC_LALT);
        tap_code(KC_KP_1);
        tap_code(KC_KP_4);
        tap_code(KC_KP_8);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_TWO_KEYS(KC_O, KC_O) {
        // Ö
        register_code(KC_LALT);
        tap_code(KC_KP_1);
        tap_code(KC_KP_5);
        tap_code(KC_KP_3);
        unregister_code(KC_LALT);
        did_leader_succeed = true;
    }

    SEQ_TWO_KEYS(KC_ENT, KC_ENT) {
        // sleep
        tap_code(KC_SYSTEM_SLEEP);
        did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_SPC) {
         // browser home
         register_code(KC_LALT);
         tap_code(KC_HOME);
         unregister_code(KC_LALT);
         did_leader_succeed = true;
      }

      SEQ_ONE_KEY(KC_ENT) {
         // browser back
         register_code(KC_LALT);
         tap_code(KC_LEFT);
         unregister_code(KC_LALT);
         did_leader_succeed = true;
      }
      
      SEQ_ONE_KEY(KC_LALT) {
         // browser forward
         register_code(KC_LALT);
         tap_code(KC_RIGHT);
         unregister_code(KC_LALT);
         did_leader_succeed = true;
      }

      SEQ_TWO_KEYS(KC_U, KC_I) {
         SEND_STRING(SENDSTRING_MM1);
         did_leader_succeed = true;
      }

      SEQ_TWO_KEYS(KC_J, KC_K) {
         SEND_STRING(SENDSTRING_MM2);
         did_leader_succeed = true;
      }

      SEQ_TWO_KEYS(KC_M, KC_COMM) {
         SEND_STRING(SENDSTRING_MM3);
         did_leader_succeed = true;
      }


    leader_end();
  }
};

void leader_start(void) {

}

void leader_end(void) {

}