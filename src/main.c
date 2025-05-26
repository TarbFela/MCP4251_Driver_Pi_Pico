#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include "hardware/spi.h"

#define LED_PIN 0

#define RESET_PIN 1
int reset_pin_check() {
    return ((sio_hw->gpio_in & (1<<RESET_PIN)) != 0);
}

#define MCP_SPI spi1
#define MCP_CS_SELECT 0
#define MCP_CS_DESELECT 1
// pinout info for SPI:
// PIN   GPIO    SPI
// 14    10      SCK
// 15    11      TX
// 16    12      RX
// 17    13      CS
#define MCP_SPI_SCK_PIN 10
#define MCP_SPI_TX_PIN 11
#define MCP_SPI_RX_PIN 12
#define MCP_SPI_CS_PIN 13

int main(void) {
    stdio_init_all();

    gpio_init(MCP_SPI_CS_PIN);
    gpio_put(MCP_SPI_CS_PIN, MCP_CS_DESELECT);
    gpio_set_dir(MCP_SPI_CS_PIN, GPIO_OUT);

    spi_init(MCP_SPI, 5*1000*1000);


    spi_set_format(MCP_SPI, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    gpio_set_function(MCP_SPI_SCK_PIN,GPIO_FUNC_SPI);
    gpio_set_function(MCP_SPI_TX_PIN,GPIO_FUNC_SPI);
    gpio_set_function(MCP_SPI_RX_PIN,GPIO_FUNC_SPI);

    sleep_ms(100);

    // the "single write" command for the MCP4251 is 16 bits
    // 4 bits addr, 2 bits cmd, 10 bits data
    // how do we want to structure this... 6 bits of constant and 10 of data.
    uint16_t mcp_single_write_data = 0x40;

    // We're wired to pot 0, so we want:
    //      address  0x00
    // Writing, so:
    //      cmd      0x00
    // 8-bit wiper, so:
    //      data     0x00 to 0xFF
    for(int j = 0; j<10; j++) {
        for (uint16_t i = 0; i < 0xFF; i++) {
            gpio_put(MCP_SPI_CS_PIN, MCP_CS_SELECT);
            //sleep_ms(10);
            spi_write16_blocking(MCP_SPI, &mcp_single_write_data, 1);
            mcp_single_write_data = i; // a little bit cheat-y but hey we're confined on i values so...
            //sleep_ms(10);
            gpio_put(MCP_SPI_CS_PIN, MCP_CS_DESELECT);
            sleep_ms(1);
        }
    }
    reset_usb_boot(0,0);
    return 0;
}