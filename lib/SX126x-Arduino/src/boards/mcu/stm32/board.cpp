/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Target board general functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/

/******************************************************************************
 * @file    board.c
 * @author  Insight SiP
 * @version V2.0.0
 * @date    30-january-2019
 * @brief   Board (module) specific functions implementation.
 *
 * @attention
 *	THIS SOFTWARE IS PROVIDED BY INSIGHT SIP "AS IS" AND ANY EXPRESS
 *	OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *	OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	DISCLAIMED. IN NO EVENT SHALL INSIGHT SIP OR CONTRIBUTORS BE
 *	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *	GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *	OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/
#if defined ARDUINO_ARCH_STM32
#include "boards/mcu/board.h"

uint32_t BoardGetRandomSeed(void)
{
	return random(255);
}

void BoardGetUniqueId(uint8_t *id)
{
	uint64_t uniqueId = 123; // TODO use UID of STM32 chip
	// Using ESP32 MAC (48 bytes only, so upper 2 bytes will be 0)
	id[7] = (uint8_t)(uniqueId >> 56);
	id[6] = (uint8_t)(uniqueId >> 48);
	id[5] = (uint8_t)(uniqueId >> 40);
	id[4] = (uint8_t)(uniqueId >> 32);
	id[3] = (uint8_t)(uniqueId >> 24);
	id[2] = (uint8_t)(uniqueId >> 16);
	id[1] = (uint8_t)(uniqueId >> 8);
	id[0] = (uint8_t)(uniqueId);
}

uint8_t BoardGetBatteryLevel(void)
{
	uint8_t batteryLevel = 0;

	//TO BE IMPLEMENTED

	return batteryLevel;
}

void BoardDisableIrq(void)
{
  noInterrupts();
}

void BoardEnableIrq(void)
{
	interrupts();
}

#endif
