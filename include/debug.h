#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG_MODE
#define DEBUG(expr) expr
#else
#define DEBUG(expr)
#endif

#endif
