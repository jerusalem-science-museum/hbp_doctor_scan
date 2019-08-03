/*
 * Doctor Scan - Simulate MRI and CT scans using 2 step motors, lasers and leds.
 * Arad Eizen 07/06/19.
 */
#include <serial_menu.h>
#include "axis.h"


/* uart baud rate in bit per seconds */
#define SERIAL_BAUD_RATE		(115200)
/* uart read timeout in milliseconds */
#define SERIAL_TIMEOUT			(1)
/* gpios mapping */
#define INJECT_DIR_PIN			(2)
#define SCAN_DIR_PIN			(3)
#define INJECT_LED_PIN			(4)
#define INJECT_STP_PIN			(5)
#define SCAN_STP_PIN			(6)
#define SCAN_LED_PIN			(7)
#define SCAN_EN_PIN				(8)
#define INJECT_EN_PIN			(9)

enum {
	SCAN_AXIS = 0,
	INJECT_AXIS,
	AXES_COUNT,
};


const uint8_t *COMMAND_LINE = command.buffer + 2;

Axis axes[] = {
	Axis(SCAN_STP_PIN, SCAN_DIR_PIN, SCAN_EN_PIN, SCAN_LED_PIN),
	Axis(INJECT_STP_PIN, INJECT_DIR_PIN, INJECT_EN_PIN, INJECT_LED_PIN),
};


void update_menu(void)
{
	int16_t a = 0, b = 0;

	if (serial_menu_update(&Serial)) {
		// switch and upper case command
		switch (command.buffer[0] & 0xDF) {
			case 'A':
				a = 500;
				b = AXIS_SPEED;
				sscanf(COMMAND_LINE, "%d %d", &a, &b);
				axes[SCAN_AXIS].setSpeedInStepsPerSecond(b);
				axes[SCAN_AXIS].move(a);
				break;
			case 'B':
				a = 500;
				b = AXIS_SPEED;
				sscanf(COMMAND_LINE, "%d %d", &a, &b);
				axes[INJECT_AXIS].setSpeedInStepsPerSecond(b);
				axes[INJECT_AXIS].move(a);
				break;
			case 'C':
				a = 0;
				sscanf(COMMAND_LINE, "%d", &a);
				axes[SCAN_AXIS].set_led(a);
				break;
			case 'D':
				a = 0;
				sscanf(COMMAND_LINE, "%d", &a);
				axes[INJECT_AXIS].set_led(a);
				break;
		}
	}
}

void setup(void)
{
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.setTimeout(SERIAL_TIMEOUT);

	for (uint8_t i = 0; i < AXES_COUNT; i++)
		axes[i].init(); 
}

void loop(void)
{
	update_menu();
	delay(1);
}
