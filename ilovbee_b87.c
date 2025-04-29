// Based off of sources from yangzheng20003
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define USB_POWER_EN_PIN B1
#define LED_POWER_EN_PIN A5
#define USB_DETECT_PIN A7
#define BAT_FULL_PIN A15
#define BAT_FULL_STATE 1

#define RGB_INDEX_CAPS 0
#define RGB_INDEX_WIN_LOCK 1
#define RGB_INDEX_BATTERY 2

enum handle_rgb_action {
    ACTION_INIT,
    ACTION_TOGGLE,
    ACTION_ON,
    ACTION_OFF,
};

static bool handle_rgb(enum handle_rgb_action action, bool pressed)
{
    static rgb_config_t rgb_last_config;

    const led_flags_t flags_on = LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT;
    const led_flags_t flags_off = LED_FLAG_NONE;
    const uint8_t mode_off = RGB_MATRIX_SOLID_COLOR;

    if (!pressed) {
        return false;
    }

    if (action == ACTION_INIT) {
        rgb_last_config = rgb_matrix_config;
        if (rgb_matrix_get_flags() == flags_off)
            rgb_matrix_mode_noeeprom(mode_off);
        else
            rgb_matrix_set_flags_noeeprom(flags_on);
        rgb_matrix_enable_noeeprom();
        return false;
    }

    if (action == ACTION_TOGGLE) {
        if (rgb_matrix_get_flags() == flags_off)
            action = ACTION_ON;
        else
            action = ACTION_OFF;
    }

    if (action == ACTION_ON) {
        rgb_matrix_config = rgb_last_config;
        rgb_matrix_set_flags(flags_on);
    } else if (action == ACTION_OFF) {
        rgb_last_config = rgb_matrix_config;
        /* note: full rgb_matrix_config is saved by rgb_matrix_set_flags() */
        rgb_matrix_set_flags(flags_off);
        rgb_matrix_mode_noeeprom(mode_off);
    }

    return false;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)
{
    if (rgb_matrix_indicators_advanced_user(led_min, led_max) == false)
        return false;

    if (host_keyboard_led_state().caps_lock)
        rgb_matrix_set_color(RGB_INDEX_CAPS, RGB_RED);
    else
        rgb_matrix_set_color(RGB_INDEX_CAPS, RGB_OFF);

    if (keymap_config.no_gui)
        rgb_matrix_set_color(RGB_INDEX_WIN_LOCK, RGB_RED);
    else
        rgb_matrix_set_color(RGB_INDEX_WIN_LOCK, RGB_OFF);

    return true;
}

void keyboard_post_init_kb(void)
{
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

#ifdef LED_POWER_EN_PIN
    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_high(LED_POWER_EN_PIN);
    gpio_set_pin_output(A9);
    gpio_write_pin_high(A9);
    gpio_set_pin_output(D2);
    gpio_write_pin_high(D2);
#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif

#ifdef USB_DETECT_PIN
    gpio_set_pin_input_high(USB_DETECT_PIN);
#endif

    handle_rgb(ACTION_INIT, true);

    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    if (process_record_user(keycode, record) == false)
        return false;

    if (keycode == QK_RGB_MATRIX_TOGGLE) {
        return handle_rgb(ACTION_TOGGLE, record->event.pressed);
    } else if (keycode == QK_RGB_MATRIX_ON) {
        return handle_rgb(ACTION_ON, record->event.pressed);
    } else if (keycode == QK_RGB_MATRIX_OFF) {
        return handle_rgb(ACTION_OFF, record->event.pressed);
    }

    return true;
}
