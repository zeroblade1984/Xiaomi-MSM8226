/*
 * arch/arm/include/asm/mutex.h
 *
 * ARM optimized mutex locking primitives
 *
 * Please look into asm-generic/mutex-xchg.h for a formal definition.
 */
#ifndef _ASM_MUTEX_H
#define _ASM_MUTEX_H

#if __LINUX_ARM_ARCH__ < 6
/* On pre-ARMv6 hardware the swp based implementation is the most efficient. */
# include <asm-generic/mutex-xchg.h>
#else

/*
 * Attempting to lock a mutex on ARMv6+ can be done with a bastardized
 * atomic decrement (it is not a reliable atomic decrement but it satisfies
 * the defined semantics for our purpose, while being smaller and faster
 * than a real atomic decrement or atomic swap.  The idea is to attempt
 * decrementing the lock value only once.  If once decremented it isn't zero,
 * or if its store-back fails due to a dispute on the exclusive store, we
 * simply bail out immediately through the slow path where the lock will be
 * reattempted until it succeeds.
 */
#include <asm-generic/mutex-xchg.h>
#endif
#endif
