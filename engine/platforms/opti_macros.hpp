#pragma once

#define PRECHARGE(var) __builtin_prefetch(&var)
#define NO_INLINE      __attribute__((noinline))
#define RARELY         __attribute__((cold))
#define FREQ           __attribute__((hot))

// Incrémentation de 1 pour ne pas exécuter une ligne ASM en plus, économie de temps d'exécution
//#define INCREMENT(var) var = (var+1)&0xFF

// Incrémentation de 1 pour ne pas exécuter une ligne ASM en plus, économie de temps d'exécution
//#define DECREMENT(var) var = (var-1)&0xFF

// Optimisation Ofast
#define MAX_OPTI     __attribute__((optimize("Ofast")))
// Optimisation O2
#define MEDIUM_OPTI  __attribute__((optimize("O2")))
// Optimisation O0
#define MIN_OPTI     __attribute__((optimize("O0")))

// Transmet au compilateur que c'est une condition qui sera peu probable, relativement à un else ou à un else if
#define IF_RARELY(conditions)    if (__builtin_expect(conditions, 0))