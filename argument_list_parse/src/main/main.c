#define DEBUG
#include "../../include/parse.h"

int main(int argc, char** argv) {
	arg_list a = arg_list_parse(argc, argv);
	arg_list_debug(a);
	arg_list_heap_deallocate(&a);
	return 0;
}