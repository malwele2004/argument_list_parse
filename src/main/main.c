#define DEBUG
#include "../../include/parse.h"

int main(int argc, char** argv) {
	char* long_args[] = {"-o","--flag"};
	arg_list a = arg_list_parse(argc, argv, 2, long_args);
	arg_list_debug(a);
	arg_list_heap_deallocate(&a);
	return 0;
}
