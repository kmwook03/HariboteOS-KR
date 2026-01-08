// interrupt
#include "../include/bootpack.h"
#include <stdio.h>

// initialize PIC
void init_pic(void)
{
    io_out8(PIC0_IMR, 0xff); // disable all interrupts
    io_out8(PIC1_IMR, 0xff); // disable all interrupts

    io_out8(PIC0_ICW1, 0x11); // edge trigger mode
    io_out8(PIC0_ICW2, 0x20); // receive INT20-27 to IRQ0-7
    io_out8(PIC0_ICW3, 1 << 2); // connect PIC1 to IRQ2
    io_out8(PIC0_ICW4, 0x01); // non-buffer mode

    io_out8(PIC1_ICW1, 0x11); // edge trigger mode
    io_out8(PIC1_ICW2, 0x28); // receive INT28-2f to IRQ8-15
    io_out8(PIC1_ICW3, 2); // connect PIC1 to IRQ2
    io_out8(PIC1_ICW4, 0x01); // non-buffer mode

    io_out8(PIC0_IMR, 0xfb); // 11111011 : disable all except PIC1
    io_out8(PIC1_IMR, 0xff); // 11111111 : disable all interrupts

    return;
}

#define PORT_KEYDAT    0x0060

struct FIFO8 keyfifo;

void inthandler21(int *esp)
{
    unsigned char data;
    io_out8(PIC0_OCW2, 0x61); // notify PIC0 that IRQ-01 has been handled
    data = io_in8(PORT_KEYDAT);
    fifo8_put(&keyfifo, data);
    
    return;
}

struct FIFO8 mousefifo;

void inthandler2c(int *esp)
{
    unsigned char data;
    io_out8(PIC1_OCW2, 0x64);
    io_out8(PIC0_OCW2, 0x62);
    data = io_in8(PORT_KEYDAT);
    fifo8_put(&mousefifo, data);
    return;
}

// When PIC be initialized, somtimes spurious interrupt occurs.
// This handler is for that.
// It just notify PIC that IRQ-07 has been handled.
// We should not process anything here.
void inthandler27(int *esp)
{
    // for PIC0 IRQ7 spurious interrupt
    io_out8(PIC0_OCW2, 0x67); // notify PIC that IRQ-07 has been handled
    return;
}
