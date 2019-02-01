#include <mcu_irqs.h>

void *vendor_vector_table[] __attribute__ ((section(".vendor_vectors"))) = {
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    0,
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    0,
    0,
    I2C0_IRQHandler,
    SCT_IRQHandler,
    MRT_IRQHandler,
    CMP_IRQHandler,
    WDT_IRQHandler,
    BOD_IRQHandler,
    0,
    WKT_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PININT0_IRQHandler,
    PININT1_IRQHandler,
    PININT2_IRQHandler,
    PININT3_IRQHandler,
    PININT4_IRQHandler,
    PININT5_IRQHandler,
    PININT6_IRQHandler,
    PININT7_IRQHandler,
};
