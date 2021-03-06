/*
 * UI.h
 *
 *  Created on: Jun 14, 2020
 *      Author: Diaa Eldeen
 */

#ifndef INCLUDE_UI_H_
#define INCLUDE_UI_H_


#include "limits.h"

#include "calculator.h"

#include "LCD.h"
#include "UART.h"




void ERROR_print(char* str);
void UI_UART();
void UI_LCD();
char* keypad_get_string();


#endif /* INCLUDE_UI_H_ */
