#include <stdint.h>

uint32_t add_result = 0U;
uint32_t x = 6U;
uint32_t y = 9U;

uint32_t add_function(uint32_t x, uint32_t y)
{
    return (x + y);
}

/*
 * Naked wrapper:
 * - Load x into r0
 * - Load y into r1
 * - Call add_function (AAPCS: r0/r1 args, return in r0)
 * - Store r0 into add_result
 * - Return with bx lr
 */
__attribute__((naked)) void call_add_function(void)
{
    __asm__ volatile(
        "ldr r0, =x           \n"
        "ldr r0, [r0]         \n"
        "ldr r1, =y           \n"
        "ldr r1, [r1]         \n"
        "bl  add_function     \n"
        "ldr r1, =add_result  \n"
        "str r0, [r1]         \n"
        "bx  lr               \n");
}

int main(void)
{
    call_add_function();
    while (1)
    {
    }
}
