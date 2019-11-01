#include QMK_KEYBOARD_H

enum my_layers {
    _QWERTY,
    _NUMS,
    _SYMMED,
    _FUNCS,
    _ADJUST
};

#define SPCNUMS LT(_NUMS, KC_SPC)
#define SPCSYMS LT(_SYMMED, KC_SPC)
#define FUNCS MO(_FUNCS)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_arrow( /* Qwerty */
    KC_GESC,    KC_Q,    KC_W,    KC_E,  KC_R, KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,     KC_A,    KC_S,    KC_D,  KC_F, KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,  KC_V, KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,
    KC_LCTL,    KC_LGUI, KC_LALT,        SPCNUMS,      SPCSYMS,       FUNCS,   KC_LEFT, KC_DOWN, KC_RIGHT
  ),
  [_NUMS] = LAYOUT_arrow( /* Numbers */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TRNS, KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_TRNS, KC_TRNS, KC_QUOT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_PGUP, KC_BSLS,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_HOME, KC_PGDN, KC_END
  ),
  [_SYMMED] = LAYOUT_arrow( /* Symbols and Media */
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TRNS, KC_UNDS, KC_PLUS, KC_COLN, KC_DQUO, KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS, KC_DQUO, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_PGUP, KC_PIPE,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_HOME, KC_PGDN, KC_END
  ),
  [_FUNCS] = LAYOUT_arrow( /* Function */
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ADJUST,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_ADJUST] = LAYOUT_arrow( /* Adjust/Reset */
    RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    EEP_RST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,  KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    // Set up RGB effects on _only_ the third LED (index 2)
    rgblight_set_effect_range(2, 1);
    // Set LED effects to breathing mode in a pink color
    rgblight_sethsv_noeeprom(255, 182, 203);
    rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 1);

    // Init the first two LEDs to a static color
    setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
    setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
}

uint32_t layer_state_set_user(uint32_t state){
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;

    if (layer_state_cmp(state, _NUMS)) {
      led0r = 255;
    }
    if (layer_state_cmp(state, _SYMMED)) {
      led0g = 255;
    }
    if (layer_state_cmp(state, _FUNCS)) {
      led1b = 255;
    }
    if (layer_state_cmp(state, _ADJUST)) {
      led1r = 255;
    }

    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
    setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
  return state;
}
