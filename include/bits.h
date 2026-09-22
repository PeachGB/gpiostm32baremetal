#ifndef BITS_H
#define BITS_H

#define BIT_SET(reg, pos) (reg |= (1 << pos))
#define BIT_CHECK(reg, pos) (reg & (1 << pos))
#define BIT_CLEAR(reg, pos) (reg &= ~(1 << pos))

#endif
