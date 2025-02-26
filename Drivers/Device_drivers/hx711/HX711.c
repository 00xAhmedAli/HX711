/*
 * HX711.c
 *
 *  Created on: Feb 21, 2025
 *      Author: tesla
 */
#include "HX711.h"

int hx711_init(Hx711_t *sensor, GPIO_TypeDef *SCK_PORT, GPIO_TypeDef *DT_PORT,uint16_t SCK_PIN, uint16_t DT_PIN) {
	sensor->DT_PIN = DT_PIN;
	sensor->SCK_PORT = SCK_PORT;
	sensor->DT_PORT = DT_PORT;
	sensor->SCK_PIN = SCK_PIN;
	GPIO_InitTypeDef G;
	G.Mode = GPIO_MODE_OUTPUT_PP;
	G.Speed = GPIO_SPEED_FREQ_LOW;
	G.Pin = sensor->SCK_PIN;
	HAL_GPIO_Init(SCK_PORT, &G);

	G.Mode = GPIO_MODE_INPUT;
	G.Pull = GPIO_NOPULL;

	G.Pin = sensor->DT_PIN;
	HAL_GPIO_Init(DT_PORT, &G);

	HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
	DWT_Delay_Init();
	return 0;
}

int hx711_read(Hx711_t *sensor) {
	uint32_t data = 0;
	uint32_t startTime = HAL_GetTick();
	while (HAL_GPIO_ReadPin(sensor->DT_PORT, sensor->DT_PIN) == GPIO_PIN_SET) {
		if (HAL_GetTick() - startTime > 200)
			return 0;
	}
	for (int8_t len = 0; len < 24; len++) {
		HAL_GPIO_WritePin(sensor->SCK_PORT, sensor->SCK_PIN, GPIO_PIN_SET);
		DWT_Delay_us(1);
		data = data << 1;
		HAL_GPIO_WritePin(sensor->SCK_PORT, sensor->SCK_PIN, GPIO_PIN_RESET);
		DWT_Delay_us(1);
		if (HAL_GPIO_ReadPin(sensor->DT_PORT, sensor->DT_PIN) == GPIO_PIN_SET)
			data++;
	}
	data = data ^ 0x800000;
	HAL_GPIO_WritePin(sensor->SCK_PORT, sensor->SCK_PIN, GPIO_PIN_SET);
	DWT_Delay_us(1);
	HAL_GPIO_WritePin(sensor->SCK_PORT, sensor->SCK_PIN, GPIO_PIN_RESET);
	DWT_Delay_us(1);
	sensor->result = data;
	return data;
}
