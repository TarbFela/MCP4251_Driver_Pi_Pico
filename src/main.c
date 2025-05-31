#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include "hardware/spi.h"

#include "MCP4251_driver.h"

#define LED_PIN 0

#define RESET_PIN 1
int reset_pin_check() {
    return ((sio_hw->gpio_in & (1<<RESET_PIN)) != 0);
}


int main(void) {
    stdio_init_all();
    sleep_ms(100);

    MCP4251_init();

    sleep_ms(10);
    for (int j = 0; j < 5000; j++)    {
        for (int i = 0; i < 256; i++) {
            float sin_val = 127 * (1 + sinf(2*M_PI * (float)i / 256.0));
            uint8_t wiper_val = (uint8_t) sin_val;
            MCP4251_write_value(wiper_val, 0);
            sleep_us(10);

        }
    }

    reset_usb_boot(0,0);
    return 0;
}