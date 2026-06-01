//
// Created by greencloud7173 on 2026/6/1.
//

#ifndef DEBUGPROBE_WS2812_H
#define DEBUGPROBE_WS2812_H
#include "hardware/pio.h"

// 驱动上下文结构体
typedef struct {
    PIO pio;
    uint sm;
    uint offset;
    uint pin;
} ws2812_instance_t;

/**
 * @brief 初始化 WS2812
 * @param instance 驱动结构体指针
 * @param pio_block 选择 pio0 或 pio1
 * @param gpio_pin 绑定的硬件引脚
 * @return 是否初始化成功
 */
bool ws2812_init(ws2812_instance_t *instance, PIO pio_block, uint gpio_pin);

/**
 * @brief 向状态机推送颜色数据
 * @param instance 驱动结构体指针
 * @param grb_color 要显示的颜色
 * @return 是否执行成功
 */
bool ws2812_write_pixel_nonblocking(ws2812_instance_t *instance, uint32_t grb_color);

#endif //DEBUGPROBE_WS2812_H
