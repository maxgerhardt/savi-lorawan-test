/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Generic lora driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis, Gregory Cristian and Wael Guibene
*/

/******************************************************************************
 * @file    timer.c
 * @author  Insight SiP
 * @version V1.0.0
 * @date    02-mars-2018
 * @brief   timer implementation functions for LORA.
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
#include "boards/mcu/timer.h"
#include "boards/mcu/board.h"
#include "STM32TimerInterrupt.h"
#include "STM32_ISR_Timer.h"

// all these timers run off of TIM3 (change if needed)
// MAKES PWM ON SOME PINS IMPOSSIBLE THAT USE THIS TIMER!!
STM32Timer ITimer(TIM3);
STM32_ISRTimer timerTicker;
uint32_t timerTimes[10];
int stm32TimerIdx[10];
bool timerInUse[10] = {false, false, false, false, false, false, false, false, false, false};

// Check timers every 100 microseconds
#define HW_TIMER_INTERVAL_US      100L

void TimerHandler()
{
  timerTicker.run();
}

void TimerConfig(void)
{
  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler);
}

void TimerInit(TimerEvent_t *obj, void (*callback)(void))
{
	// Look for an available Ticker
	for (int idx = 0; idx < 10; idx++)
	{
		if (timerInUse[idx] == false)
		{
			timerInUse[idx] = true;
			obj->timerNum = idx;
			obj->Callback = callback;
			return;
		}
	}
	LOG_LIB("TIM", "No more timers available!");
	/// \todo We run out of tickers, what do we do now???
}

void TimerStart(TimerEvent_t *obj)
{
	int idx = obj->timerNum;
	if (obj->oneShot)
	{
		stm32TimerIdx[idx] = timerTicker.setTimeout(timerTimes[idx], obj->Callback);
	}
	else
	{
		stm32TimerIdx[idx] = timerTicker.setInterval(timerTimes[idx], obj->Callback);
	}
}

void TimerStop(TimerEvent_t *obj)
{
	int idx = obj->timerNum;
	timerTicker.disable(stm32TimerIdx[idx]);
}

void TimerReset(TimerEvent_t *obj)
{
	int idx = obj->timerNum;
	timerTicker.disable(stm32TimerIdx[idx]);
	if (obj->oneShot)
	{
		stm32TimerIdx[idx] = timerTicker.setTimeout(timerTimes[idx], obj->Callback);
	}
	else
	{
		stm32TimerIdx[idx] = timerTicker.setInterval(timerTimes[idx], obj->Callback);
	}
}

void TimerSetValue(TimerEvent_t *obj, uint32_t value)
{
	int idx = obj->timerNum;
	timerTimes[idx] = value;
}

TimerTime_t TimerGetCurrentTime(void)
{
	return millis();
}

TimerTime_t TimerGetElapsedTime(TimerTime_t past)
{
	uint32_t nowInTicks = millis();
	uint32_t pastInTicks = past;
	TimerTime_t diff = nowInTicks - pastInTicks;

	return diff;
}

#endif