/* Arbitrary precision integer functions. */

#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#include <linux/kernel.h>
#include "apm.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    apm_digit *digits; /* Digits of number. */
    apm_size size;     /* Length of number. */
    apm_size alloc;    /* Size of allocation. */
    unsigned sign : 1; /* Sign bit. */
} bn, bn_t[1];

#define BN_INITIALIZER                                        \
    {                                                         \
        {                                                     \
            .digits = NULL, .size = 0, .alloc = 0, .sign = 0, \
        }                                                     \
    }

void bn_init(bn *p);
void bn_init_u32(bn *p, uint32_t q);
void bn_free(bn *p);

void bn_set_u32(bn *p, uint32_t q);

#define bn_is_zero(n) ((n)->size == 0)
void bn_zero(bn *p);

void bn_swap(bn *a, bn *b);

void bn_lshift(const bn *q, unsigned int bits, bn *p);

/* S = A + B */
void bn_add(const bn *a, const bn *b, bn *s);

/* P = A * B */
void bn_mul(const bn *a, const bn *b, bn *p);

/* B = A * A */
void bn_sqr(const bn *a, bn *b);

void bn_fprint(const bn *n, unsigned int base);
#define bn_print(n, base) bn_fprint((n), (base))
#define bn_print_dec(n) bn_print((n), 10)
#define bn_print_hex(n) bn_print((n), 16)

void bn_ufprint(const bn *n, unsigned int base, char *const kbuf);
#define bn_uprint(n, base, kbuf) bn_ufprint((n), (base), (kbuf))
#define bn_uprint_dec(n, kbuf) bn_uprint((n), 10, (kbuf))
#define bn_uprint_hex(n, kbuf) bn_uprint((n), 16, (kbuf))

#ifdef __cplusplus
}
#endif

#endif /* !_BIGNUM_H_ */
