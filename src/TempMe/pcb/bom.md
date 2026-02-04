# MCU

STM32L031G4U6

STM32L031G4U6 Pin Configuration (UFQFPN28)
The following pinout is for the STM32L031G4U6 in the UFQFPN28 (28-pin) package. This is based on the STMicroelectronics datasheet DS10663.

|Pin Number	|Pin Name	|Main Function / Notes|
|---|---|---|
| 1|	VDD	|Digital Power Supply|
|2	PC14-OSC32_IN	|Low Speed External Clock Input|
|3	PC15-OSC32_OUT	|Low Speed External Clock Output|
|4	NRST	|Device Reset (Active Low)|
|5	VDDA	|Analog Power Supply|
|6	PA0	|GPIO / ADC_IN0|
|7	PA1	|GPIO / ADC_IN1|
|8	PA2	|GPIO / ADC_IN2 / USART2_TX|
|9	PA3	|GPIO / ADC_IN3 / USART2_RX|
|10	PA4	|GPIO / ADC_IN4 / SPI1_NSS|
|11	PA5	|GPIO / ADC_IN5 / SPI1_SCK|
|12	PA6	|GPIO / ADC_IN6 / SPI1_MISO|
|13	PA7	|GPIO / ADC_IN7 / SPI1_MOSI|
|14	PB0	|GPIO / ADC_IN8|
|15	PB1	|GPIO / ADC_IN9|
|16	VSS	|Ground|
|17	VDD	|Digital Power Supply|
|18	PA8	|GPIO / MCO|
|19	PA9	|GPIO / USART1_TX|
|20	PA10	|GPIO / USART1_RX|
|21	PA11	|GPIO|
|22	PA12	|GPIO|
|23	PA13	|GPIO / SWDIO (Debug)|
|24	PA14	|GPIO / SWCLK (Debug)|
|25	PA15	|GPIO|
|26	PB3	|GPIO|
|27	PB4	|GPIO|
|28	PB5	|GPIO|


Key Hardware Notes
Power: Connect both VDD pins (1 and 17) to your 3.3V supply and VSS (pin 16) to Ground.
Bootloader: In the 28-pin package, there is no dedicated BOOT0 pin. Boot mode is configured via the nBOOT0 and BOOT0 option bits in the Flash memory.
Debug: Use PA13 (SWDIO) and PA14 (SWCLK) for programming and debugging via ST-Link.
Exposed Pad: The UFQFPN28 package has an exposed thermal pad that should be connected to VSS (Ground).