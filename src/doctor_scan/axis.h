#ifndef _AXIS_H_
#define _AXIS_H_

#include <Arduino.h>
#include <SpeedyStepper.h>

#define AXIS_SPEED				(200)
#define AXIS_ACCL				(800)


class Axis : public SpeedyStepper
{
public:
    Axis(uint8_t step_pin, uint8_t dir_pin, uint8_t en_pin, uint8_t led_pin);
	void init(void);
	void move(int16_t steps, uint16_t speed=AXIS_SPEED);
	void set_led(bool is_on);
private:
	uint8_t _step_pin;
	uint8_t _dir_pin;
	uint8_t _en_pin;
	uint8_t _led_pin;
};

#endif
