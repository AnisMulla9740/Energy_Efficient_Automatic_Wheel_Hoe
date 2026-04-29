/*
 * lcd_i2c.c
 *
 *  Created on: Apr 20, 2026
 *      Author: Anis
 */


#include "lcd_i2c.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR (0x27 << 1)  // change to (0x3F<<1) if needed

#define RS 0x01
#define EN 0x04
#define BL 0x08

static void lcd_write_nibble(uint8_t nibble, uint8_t control)
{
    uint8_t data = (nibble & 0xF0) | control | BL;
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, HAL_MAX_DELAY);

    data |= EN;
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, HAL_MAX_DELAY);

    data &= ~EN;
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, HAL_MAX_DELAY);
}

void lcd_send_cmd(char cmd)
{
    lcd_write_nibble(cmd & 0xF0, 0);
    lcd_write_nibble((cmd << 4) & 0xF0, 0);
    HAL_Delay(2);
}

void lcd_send_data(char data)
{
    lcd_write_nibble(data & 0xF0, RS);
    lcd_write_nibble((data << 4) & 0xF0, RS);
    HAL_Delay(2);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_set_cursor(int row, int col)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
}

void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++);
}

void lcd_init(void)
{
    HAL_Delay(50);

    lcd_write_nibble(0x30, 0);
    HAL_Delay(5);
    lcd_write_nibble(0x30, 0);
    HAL_Delay(1);
    lcd_write_nibble(0x30, 0);
    HAL_Delay(10);
    lcd_write_nibble(0x20, 0);

    lcd_send_cmd(0x28); // 4-bit, 2-line
    lcd_send_cmd(0x08); // display off
    lcd_send_cmd(0x01); // clear
    lcd_send_cmd(0x06); // entry mode
    lcd_send_cmd(0x0C); // display on
}
