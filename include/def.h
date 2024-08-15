#ifndef DEF
#define DEF

typedef struct {
	int is_short;
	char fused_short_option[2];
	char* option;
	char* body;
} arg_option ;

typedef struct {
	int nargs, noptions;
	arg_option* aopt;
} arg_list;

#endif
