/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Layers
enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    SYM,
    NAV,
    NUM,
};

// Home Row Mods (macOS)
// Left hand
#define HM_A    LCTL_T(KC_A)    // A: tap a, hold Left Ctrl
#define HM_S    LALT_T(KC_S)    // S: tap s, hold Left Option
#define HM_D    LGUI_T(KC_D)    // D: tap d, hold Left Command
#define HM_F    LSFT_T(KC_F)    // F: tap f, hold Left Shift

// Right hand
#define HM_J    RSFT_T(KC_J)    // J: tap j, hold Right Shift
#define HM_K    RGUI_T(KC_K)    // K: tap k, hold Right Command
#define HM_L    RALT_T(KC_L)    // L: tap l, hold Right Option
#define HM_SCLN RCTL_T(KC_SCLN) // ;: tap ;, hold Right Ctrl

// Transparent helper
#define _______ KC_TRNS

// Custom keycodes for Cmd+C / Cmd+V
enum custom_keycodes {
    CMD_C = SAFE_RANGE,
    CMD_V,
};

// Macros for Cmd+C and Cmd+V on macOS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_C:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LGUI));
                register_code(KC_C);
            } else {
                unregister_code(KC_C);
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case CMD_V:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LGUI));
                register_code(KC_V);
            } else {
                unregister_code(KC_V);
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ─────────────────────────────
    // MAC_BASE – homerow mods, Space=SYM, Caps(tap Esc / hold NAV), V=NUM
    // ─────────────────────────────
    [MAC_BASE] = LAYOUT_90_ansi(
        KC_MUTE,    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        MC_1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,             KC_PGUP,
        MC_2,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,            KC_PGDN,
        MC_3,       LT(NAV, KC_ESC),  HM_A,    HM_S,    HM_D,    HM_F,    KC_G,      KC_H,     HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,            KC_ENT,             KC_HOME,
        MC_4,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     LT(NUM, KC_V), KC_B,     KC_B, KC_N, KC_M,  KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,  KC_UP,
        MC_5,       KC_LCTL,  KC_LOPTN,           KC_LCMMD, LT(SYM, KC_SPC), MO(MAC_FN),       LT(SYM, KC_SPC),          KC_RCMMD, KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    // ─────────────────────────────
    // MAC_FN – multimedia/system jak stock Q10 Pro
    // ─────────────────────────────
    [MAC_FN] = LAYOUT_90_ansi(
        RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,            _______,  _______,  _______),

    // ─────────────────────────────
    // WIN_BASE – jak stock (bez homerow mods)
    // ─────────────────────────────
    [WIN_BASE] = LAYOUT_90_ansi(
        KC_MUTE,    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        MC_1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,            KC_PGUP,
        MC_2,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,            KC_PGDN,
        MC_3,       KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        MC_4,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        MC_5,       KC_LCTL,  KC_LWIN,            KC_LALT,  KC_SPC,  MO(WIN_FN),           KC_SPC,             KC_RALT,            KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_90_ansi(
        RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,            _______,  _______,  _______),

    // ─────────────────────────────
    // SYM – warstwa symboliczna (SpaceFN)
    // ─────────────────────────────
    [SYM] = LAYOUT_90_ansi(
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  KC_EXLM,  KC_AT,    KC_DLR,   KC_HASH,  _______,   _______,  KC_AMPR,  KC_ASTR,  KC_UNDS,  KC_PLUS,  KC_BSLS,  _______,  _______,            _______,
        _______,    _______,  KC_CIRC,  KC_GRV,   KC_TILD,  KC_PERC,  _______,   KC_LBRC,  KC_LPRN,  KC_RPRN,  KC_MINS,  KC_EQL,   KC_PIPE,            _______,            _______,
        _______,    _______,            KC_0,     _______,  CMD_C,    CMD_V,     _______,  _______,  KC_RBRC,  KC_LCBR,  KC_RCBR,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,            _______,  _______,  _______),

    // ─────────────────────────────
    // NAV – warstwa nawigacyjna (CapsFN)
    // ─────────────────────────────
    [NAV] = LAYOUT_90_ansi(
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,            _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,            _______,  _______,  _______),

    // ─────────────────────────────
    // NUM – warstwa numeryczna (V)
    // ─────────────────────────────
    [NUM] = LAYOUT_90_ansi(
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_7,     KC_8,     KC_9,     _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   KC_DOT,   KC_4,     KC_5,     KC_6,     KC_0,     _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  KC_1,     KC_2,     KC_3,     _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,            _______,  _______,  _______),
    };

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [SYM]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [NAV]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [NUM]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif // ENCODER_MAP_ENABLE
