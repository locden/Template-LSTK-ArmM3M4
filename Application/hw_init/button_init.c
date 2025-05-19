#include <button_init.h>

void btn_inc_init() {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /*Configure GPIO pins : PCPin PCPin */
	  GPIO_InitStruct.Pin  = SW2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
uint8_t btn_inc_read() {

	return HAL_GPIO_ReadPin(SW1_GPIO_Port , SW1_Pin);
}

void btn_dec_init() {
		GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /*Configure GPIO pins : PCPin PCPin */
	  GPIO_InitStruct.Pin  = SW2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
uint8_t btn_dec_read() {
	return HAL_GPIO_ReadPin(SW2_GPIO_Port , SW2_Pin);
}

void btn_startPause_init() {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin  = SW_BOARD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(SW_BOARD_GPIO_Port, &GPIO_InitStruct);
}
uint8_t btn_startPause_read() {
	return HAL_GPIO_ReadPin(SW_BOARD_GPIO_Port , SW_BOARD_Pin);
}



