#include "fixed.h"

extern inline fixed int_to_fixed(int value)
{
    return (value << 16);
}

extern inline int fixed_to_int(fixed value)
{
    if (value < 0) return (value >> 16 - 1);
    return (value >> 16);
}

extern inline int round_fixed(fixed value)
{
    return fixed_to_int(value + (1 << 15));
}

extern inline fixed double_to_fixed(double value)
{
    return round(value * (65536.0));
}

extern inline fixed float_to_fixed(float value)
{
    return roundf(value * (65536.0f));
}

extern inline fixed frac_to_fixed(int a, int b)
{
    return (a << 16) / b;
}