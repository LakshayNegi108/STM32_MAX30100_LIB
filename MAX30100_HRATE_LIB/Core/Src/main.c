#include "main.h"

#include "BML_DEF.h"
#include "rcc.h"
#include "uart.h"
#include "i2c.h"
#include "MAX30100_PulseOximeter.h"
//#include "MAX30100.h"

BML_StatusTypeDef ret;

// Sampling is tightly related to the dynamic range of the ADC.
// refer to the datasheet for further info
#define SAMPLING_RATE                       MAX30100_SAMPRATE_100HZ
// The LEDs currents must be set to a level that avoids clipping and maximises the
// dynamic range
#define IR_LED_CURRENT                      MAX30100_LED_CURR_50MA
#define RED_LED_CURRENT                     MAX30100_LED_CURR_27_1MA

// The pulse width of the LEDs driving determines the resolution of
// the ADC (which is a Sigma-Delta).
// set HIGHRES_MODE to true only when setting PULSE_WIDTH to MAX30100_SPC_PW_1600US_16BITS
#define PULSE_WIDTH                         MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE                        true

void Tester() {
	ret = MAX30100_begin();
	if (ret == BML_OK) {
		print("Successful\n");
	} else {
		print("Error: ");
		uint8_t partID = MAX30100_getPartId();
		if (partID == 0xff) {
			print("I2C Error");
		} else {
			print("wrong part ID 0x%X", partID);
			print(" (expected: 0x%X\n", EXPECTED_PART_ID);
		}
		return;
	}

	print("Enabling HR/SPO2 mode..");
	MAX30100_setMode(MAX30100_MODE_SPO2_HR);
	print("Done\n");

	print("Configuring LEDs biases to 50mA..");
	MAX30100_setLedsCurrent(MAX30100_LED_CURR_50MA, MAX30100_LED_CURR_27_1MA);
	print("Done\n");

	print("Setting Sampling rate to 100Hz..");
	MAX30100_setSamplingRate(MAX30100_SAMPRATE_100HZ);
	print("Done\n");

	print("Enabling High Resolution Mode..");
	MAX30100_setHighresModeEnabled(true);
	print("Done\n");

	print("Lowering the current to 7.6mA..");
	MAX30100_setLedsCurrent(MAX30100_LED_CURR_7_6MA, MAX30100_LED_CURR_7_6MA);
	print("Done\n");

	Delay(1000);
	print("Shutting Down..");
	MAX30100_shutdown();
	print("Done\n");

	Delay(1000);
	print("Resuming normal operation..");
	MAX30100_resume();
	Delay(500);
	print("Done\n");

	uint32_t tsTempSampStart = HAL_GetTick();
	print("Sampling die temperature..");
	MAX30100_startTemperatureSampling();
	while (!MAX30100_isTemperatureReady()) {
		if (HAL_GetTick() - tsTempSampStart > 1000) {
			print("ERROR: timeout\n");
			return;
		}
	}

	float temperature = MAX30100_retrieveTemperature();
	print("Done, temp = %f'C\n", temperature);

	if (temperature < 5) {
		print("WARNING: Temperature probe reported an odd value\n");
	} else {
		print("All test passed\n");
	}

	//	print("Press any key to go into sampling loop mode\n");
	//	while (!USART_READ(USART2))
	//		;

	MAX30100_resetFifo();
}

void max30100_configfun() {
	MAX30100_setMode(MAX30100_MODE_SPO2_HR);
	MAX30100_setLedsCurrent(MAX30100_LED_CURR_7_6MA, MAX30100_LED_CURR_7_6MA);
	MAX30100_setSamplingRate(MAX30100_SAMPRATE_100HZ);
	MAX30100_setHighresModeEnabled(true);
}

int main(void) {
	RCC_CONFIG_48MHZ();
	uart_print_config(9600);
	print("Running\n");

	if (!PulseOximeter_begin(PULSEOXIMETER_DEBUGGINGMODE_RAW_VALUES)) {
		print("Failed\n");
	} else {
		print("Success\n");
	}
	PulseOximeter_setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

//	uint16_t ir = 0;
//	uint16_t red = 0;
	float ir = 0;
	float red = 0;

	uint8_t MAX30100_ready = 1;
	uint16_t tsLastReport = 0;

	while (1) {

		if (PulseOximeter_update() != BML_OK) {
			print("Error Updating\n");
			PulseOximeter_begin(PULSEOXIMETER_DEBUGGINGMODE_NONE);
			MAX30100_ready = 0;
		} else {
			MAX30100_ready = 1;
		}
		if (MAX30100_ready) {
			if (HAL_GetTick() - tsLastReport > 100) {
				ir = PulseOximeter_getHeartRate();
				red = PulseOximeter_getSpO2();
//				print("                     Float: %0.2f, %0.2f\n\r", ir, red);

				tsLastReport = HAL_GetTick();
			}
		}
		MAX30100_resetFifo();
	}

	return 0;
}


/*

#include "main.h"

#include "BML_DEF.h"
#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "MAX30100.h"

BML_StatusTypeDef ret;

// Sampling is tightly related to the dynamic range of the ADC.
// refer to the datasheet for further info
#define SAMPLING_RATE                       MAX30100_SAMPRATE_100HZ
// The LEDs currents must be set to a level that avoids clipping and maximises the
// dynamic range
#define IR_LED_CURRENT                      MAX30100_LED_CURR_50MA
#define RED_LED_CURRENT                     MAX30100_LED_CURR_27_1MA

// The pulse width of the LEDs driving determines the resolution of
// the ADC (which is a Sigma-Delta).
// set HIGHRES_MODE to true only when setting PULSE_WIDTH to MAX30100_SPC_PW_1600US_16BITS
#define PULSE_WIDTH                         MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE                        true

void Tester() {
	ret = MAX30100_begin();
	if (ret == BML_OK) {
		print("Successful\n");
	} else {
		print("Error: ");
		uint8_t partID = MAX30100_getPartId();
		if (partID == 0xff) {
			print("I2C Error");
		} else {
			print("wrong part ID 0x%X", partID);
			print(" (expected: 0x%X\n", EXPECTED_PART_ID);
		}
		return;
	}

	print("Enabling HR/SPO2 mode..");
	MAX30100_setMode(MAX30100_MODE_SPO2_HR);
	print("Done\n");

	print("Configuring LEDs biases to 50mA..");
	MAX30100_setLedsCurrent(MAX30100_LED_CURR_50MA, MAX30100_LED_CURR_27_1MA);
	print("Done\n");

	print("Setting Sampling rate to 1000Hz..");
	MAX30100_setSamplingRate(MAX30100_SAMPRATE_1000HZ);
	print("Done\n");

	print("Enabling High Resolution Mode..");
	MAX30100_setHighresModeEnabled(true);
	print("Done\n");

	print("Lowering the current to 7.6mA..");
	MAX30100_setLedsCurrent(MAX30100_LED_CURR_7_6MA, MAX30100_LED_CURR_7_6MA);
	print("Done\n");

	Delay(1000);
	print("Shutting Down..");
	MAX30100_shutdown();
	print("Done\n");

	Delay(1000);
	print("Resuming normal operation..");
	MAX30100_resume();
	Delay(500);
	print("Done\n");

	uint32_t tsTempSampStart = HAL_GetTick();
	print("Sampling die temperature..");
	MAX30100_startTemperatureSampling();
	while (!MAX30100_isTemperatureReady()) {
		if (HAL_GetTick() - tsTempSampStart > 1000) {
			print("ERROR: timeout\n");
			return;
		}
	}

	float temperature = MAX30100_retrieveTemperature();
	print("Done, temp = %f'C\n", temperature);

	if (temperature < 5) {
		print("WARNING: Temperature probe reported an odd value\n");
	} else {
		print("All test passed\n");
	}

	//	print("Press any key to go into sampling loop mode\n");
	//	while (!USART_READ(USART2))
	//		;

	MAX30100_resetFifo();
}

void max30100_configfun() {
	MAX30100_setMode(MAX30100_MODE_SPO2_HR);
	MAX30100_setLedsCurrent(MAX30100_LED_CURR_7_6MA, MAX30100_LED_CURR_7_6MA);
	MAX30100_setSamplingRate(MAX30100_SAMPRATE_1000HZ);
	MAX30100_setHighresModeEnabled(true);
}

int main(void) {
	RCC_CONFIG_48MHZ();
	uart_print_config(9600);
	print("Running\n");

	Tester();
//	MAX30100_begin();
	max30100_configfun();
	uint32_t start = 0;
	uint32_t end = 0;

	uint16_t ir = 0;
	uint16_t red = 0;
	uint8_t MAX30100_ready = 1;

	while (1) {
		start = HAL_GetTick();
		ret = MAX30100_update();
		if (ret != BML_OK) {
			print("ERROR in MAX30100...Retrying\n");
			if(MAX30100_begin() == BML_OK){
				max30100_configfun();
				MAX30100_resetFifo();
				MAX30100_ready = 1;
			}
			else{
				MAX30100_ready = 0;
				Delay(500);
			}


		} else if (ret == BML_OK) {
			MAX30100_ready = 1;
		}

		if (MAX30100_ready) {
			if (MAX30100_getRawValues(&ir, &red)) {
				print("IR: %d, RED: %d\n", ir, red);
			}
		}

	}

	return 0;
}

*/
