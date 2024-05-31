#if defined ARDUINO_ARCH_STM32
#include <SPI.h>
#include "boards/mcu/board.h"

SPIClass SPI_LORA;

void initSPI(void)
{
	SPI_LORA.setSCLK(_hwConfig.PIN_LORA_SCLK);
	SPI_LORA.setMISO(_hwConfig.PIN_LORA_MISO);
	SPI_LORA.setMOSI(_hwConfig.PIN_LORA_MOSI);
	// chip select is explicitly managed with digitalWrite()
	// don't assume this is a hardware chip select pin
	//SPI_LORA.setSSEL(_hwConfig.PIN_LORA_NSS);
	SPI_LORA.begin();
}
#endif