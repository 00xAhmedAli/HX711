/*
 * HX711.h
 *
 *  Created on: Feb 21, 2025
 *      Author: tesla
 */

#ifndef DEVICE_DRIVERS_HX711_HX711_H_
#define DEVICE_DRIVERS_HX711_HX711_H_
#include "stm32f1xx_hal.h"
#include "Delay_Micros/dwt_stm32_delay.h"

#include <stdint.h>

typedef struct {
	int32_t result;

	GPIO_TypeDef *SCK_PORT;
	GPIO_TypeDef *DT_PORT;
	uint16_t SCK_PIN;
	uint16_t DT_PIN;

} Hx711_t;

int hx711_init(Hx711_t *sensor, GPIO_TypeDef *SCK_Port, GPIO_TypeDef *DT_PORT,
		uint16_t SK_PIN, uint16_t DT_PIN);

int hx711_read(Hx711_t *sensor);

#endif /* DEVICE_DRIVERS_HX711_HX711_H_ */
