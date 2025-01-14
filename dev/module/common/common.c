#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "compile_flag.h"
#include "co_math.h"

ROM_SYMBOL void rand_gen_by_word(uint8_t *ptr,uint8_t word_num)
{
    while(word_num--)
    {
        uint32_t x = rand_fn();
        memcpy(ptr,&x,sizeof(uint32_t));    
        ptr += sizeof(uint32_t);
    }
}

ROM_SYMBOL void memcpy32(uint32_t *dest, const uint32_t *src, uint32_t size_word)
{
    while(size_word--)
    {
        *dest++ = *src++;
    }
}

// ROM_SYMBOL int32_t time_diff(uint32_t time0,uint32_t time1)
// {
//     int32_t diff = time0 - time1;
//     return diff;
// }

ROM_SYMBOL uint8_t count_trailing_zeros(uint32_t x)
{
    uint32_t i;
    for (i = 0; i < 32; i++)
    {
        if (x & 1<<i )
            break;
    }
    return i;
}


uint32_t __attribute__((weak)) __div64_32(uint64_t *n, uint32_t base)  //from linux kernel lib/math/div64.c
{
	uint64_t rem = *n;
	uint64_t b = base;
	uint64_t res, d = 1;
	uint32_t high = rem >> 32;

	/* Reduce the thing a bit first */
	res = 0;
	if (high >= base) {
		high /= base;
		res = (uint64_t) high << 32;
		rem -= (uint64_t) (high*base) << 32;
	}

	while ((int64_t)b > 0 && b < rem) {
		b = b+b;
		d = d+d;
	}

	do {
		if (rem >= b) {
			rem -= b;
			res += d;
		}
		b >>= 1;
		d >>= 1;
	} while (d);

	*n = res;
	return rem;
}
