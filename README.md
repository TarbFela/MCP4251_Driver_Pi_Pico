# [WIP] SPI Digital Potentiometer driver for Pi Pico
**Device:** MCP4251

As it stands, this project drives the wiper of an MCP4251 through its full 8-bit
range. Connecting the A and B pins to VBUS and GND gives a sawtooth at the wiper (all P0).

## Notes to self
1. SPI init involves message size configuration (16 bits)
2. MCP4251 works in two modes. The mode is determined by the status of SCK when CS is pulled low.
3. 