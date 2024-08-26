#include <stdio.h>
#include <stdint.h>

uint32_t update(uint32_t input, int bit)
{
    uint32_t updateAt = 1 << bit;
    printf("updateAt = %x\n", updateAt);
    return (input | updateAt);
}

uint32_t reset(uint32_t input, int bit)
{
    uint32_t resetAt = ~(1 << bit);
    printf("resetAt = %x\n", resetAt);
    return (input & resetAt); 
}

int main()
{
    uint32_t input = 0x345689AB;
    uint32_t output = reset(input, 1);
    printf("Input = %x | ouput = %x\n", input, output);
    return 0;
}