#include "def.h"

#include "def.h"

#ifndef ARG_LIST_PARSE
#define ARG_LIST_PARSE

#ifdef DEBUG
extern void arg_list_debug(arg_list alist);
#endif

extern arg_list arg_list_parse(int argc, char** argv, int nlargs, char** long_args);

extern void arg_list_heap_deallocate(arg_list* alist_ptr);

#endif
