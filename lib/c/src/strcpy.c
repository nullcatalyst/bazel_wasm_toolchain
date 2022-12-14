#include <limits.h>
#include <stdint.h>
#include <string.h>

#undef strcpy

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1 / UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
#define HASZERO(x) ((x)-ONES & ~(x)&HIGHS)

char* strcpy(char* __restrict d, const char* __restrict s) {
#ifdef __GNUC__
    typedef size_t __attribute__((__may_alias__)) word;
    word*       wd;
    const word* ws;
    if ((uintptr_t)s % ALIGN == (uintptr_t)d % ALIGN) {
        for (; (uintptr_t)s % ALIGN; s++, d++) {
            if (!(*d = *s)) return d;
        }
        wd = (void*)d;
        ws = (const void*)s;
        for (; !HASZERO(*ws); *wd++ = *ws++) {
            // continue;
        }
        d = (void*)wd;
        s = (const void*)ws;
    }
#endif
    for (; (*d = *s); s++, d++) {
        // continue;
    }

    return d;
}
