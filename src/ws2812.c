//
// Created by greencloud7173 on 2026/6/1.
//

#include "ws2812.h"
#include "ws2812.pio.h"

bool ws2812_init(ws2812_instance_t *instance, PIO pio_block, uint gpio_pin) {
    instance->pio = pio_block;
    instance->pin = gpio_pin;

    if (!pio_can_add_program(instance->pio, &ws2812_program)) {
        return false;
    }
    instance->offset = pio_add_program(instance->pio, &ws2812_program);

    int claimed_sm = pio_claim_unused_sm(instance->pio, false);
    if (claimed_sm < 0) {
        return false;
    }
    instance->sm = (uint)claimed_sm;

    ws2812_program_init(instance->pio, instance->sm, instance->offset, instance->pin, 800000, false);

    return true;
}

bool ws2812_write_pixel_nonblocking(ws2812_instance_t *instance, uint32_t grb_color) {
    if (pio_sm_is_tx_fifo_full(instance->pio, instance->sm)) {
        return false;
    }

    pio_sm_put(instance->pio, instance->sm, grb_color << 8u);
    return true;
}