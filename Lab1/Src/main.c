#include <stdint.h>

uint32_t add_result = 0U;
uint32_t x = 6U;
uint32_t y = 9U;

uint32_t add_function(uint32_t x, uint32_t y)
{
    return (x + y);
}

/*
 * Challenge:
 * - Cortex-M4 calling convention
 * - function is naked
 * - call add_function(x, y)
 * - store result into add_result
 */
__attribute__((naked)) void call_add_function(void)
{
    __asm__ volatile(
               "\n"
    );
}

int main(void)
{
    call_add_function();
    while (1);
}
