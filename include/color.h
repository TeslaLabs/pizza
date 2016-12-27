#ifndef ACOMP_ERROR_H
#define ACOMP_ERROR_H

#include <cstdio>

#define ERROR(msg) "\033[47;31;1m" msg "\033[0m"
#define RED(msg) "\033[31m" msg "\033[0m"
#define BLUE(msg) "\033[34m" msg "\033[0m"
#define GREEN(msg) "\033[32m" msg "\033[0m"
#define PURPLE(msg) "\033[35m" msg "\033[0m"

#endif
