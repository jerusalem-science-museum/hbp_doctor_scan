#include "axis.h"

Axis::Axis(uint8_t step_pin, uint8_t dir_pin, uint8_t en_pin, uint8_t led_pin)
{
	_step_pin = step_pin;
	_dir_pin = dir_pin;
	_en_pin = en_pin;
	_led_pin = led_pin;
}

void Axis::init(void)
{
	pinMode(_en_pin, OUTPUT);
	pinMode(_led_pin, OUTPUT);
	set_led(false);
	move(0);
	SpeedyStepper::connectToPins(_step_pin, _dir_pin);
	SpeedyStepper::setAccelerationInStepsPerSecondPerSecond(AXIS_ACCL);
}

void Axis::move(int16_t steps, uint16_t speed)
{
	digitalWrite(_en_pin, false);
	SpeedyStepper::moveRelativeInSteps(steps);
	digitalWrite(_en_pin, true);
}

void Axis::set_led(bool is_on)
{
	digitalWrite(_led_pin, is_on);
}
