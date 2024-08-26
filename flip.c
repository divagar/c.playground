#include <stdio.h>
#include <stdint.h>

uint32_t flip(uint32_t input)
{
    // ectract last 1 byte and add
    uint32_t output = 0x0;
    uint8_t temp = 0x0;
    for (int i = 0; i < 4; i++)
    {
        temp = input >> (8 * i) & 0xFF;
        output = output << 8;
        output += temp;
    }

    return output;
}

int main()
{
    uint32_t input = 0x345176DC;
    uint32_t output = flip(input);
    printf("Input = 0x%x | output = ox%x\n", input, output);

    return 0;
}