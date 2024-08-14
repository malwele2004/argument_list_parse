#include <stdio.h>
#include <stdlib.h>
#include "../../include/def.h"
#define HYPHEN '-'
#define OPTION_SHRT "short"
#define OPTION_LONG "long"

// unsafe: arg should not be NULL
// if ao is NULL, it isn't used
char* read_option(arg_option* ao, char* arg) {
	if (ao)
		ao->is_short = 1; // Assume short option

	if (arg[0] == HYPHEN) { // Option
		if (arg[1] == HYPHEN) { // long
			if (ao)
				ao->is_short = 0; // Set to long option
			return arg+2;
		}
		// short
		return arg+1;
	}
	return NULL;
}

// Unsafe: No safety checks of nargs
// Used internally
// nargs is checked by parse [Which uses this]
arg_list arg_list_heap_allocate(int nargs) {
	arg_list alist = (arg_list){0,0,0};
	alist.aopt = calloc(nargs,sizeof(arg_option));
	if (alist.aopt) {
		alist.nargs = 
		alist.noptions = nargs; // Options will be adjusted
	}
	return alist;
}

void arg_list_heap_deallocate(arg_list* alist_ptr) {
	if (alist_ptr->aopt) {
		free(alist_ptr->aopt);
		alist_ptr->aopt = NULL;
		alist_ptr->nargs = alist_ptr->noptions = 0;
	}
}

// Unsafe: used internally, no checks on alist_ptr
// and found[actual number of found options]
void arg_list_adjust_noption(arg_list* alist_ptr, int found) {
	if (found < 0) { // (-Inf,0)
		// Overflow and/or error
		#ifdef DEBUG
			puts("(arg_list_adjust_noption) [found < 0]");
		#endif
	} else if (found > 0 && found < alist_ptr->noptions) { // (0,alist_ptr->noptions) == [1,alist_ptr->noptions)
		long nbytes = sizeof(arg_option) * found;
		arg_option* aopt = realloc(alist_ptr->aopt,nbytes);
		if (aopt) { // Successful
			alist_ptr->noptions = found;
			alist_ptr->aopt = aopt;
		} else {
			#ifdef DEBUG
				puts("(arg_list_adjust_noption) [realloc to smaller size failed]");
			#endif
		}
	} else { // 0 and [alist_ptr->noptions,+Inf)
		// both cases shouldn't happen
		// asserted nargs >= 1 and nargs is used therefore option-value pairs should be fewer
		// found == 0 or found >= noptions
		#ifdef DEBUG
			puts("(arg_list_adjust_noption) [found == 0 or found >= noptions]");
		#endif
	}
}

void arg_list_debug(arg_list alist) {
	if (alist.aopt) {
		printf("\narg_list\nnargs: %d\nnoptions: %d\n",
		alist.nargs, alist.noptions);

		for (int i = 0; i < alist.noptions ; i++) {
			printf("Option[%d] {type: %s, option: %s, value: %s}\n",
						 i+1,
						 (alist.aopt[i].is_short) ? OPTION_SHRT :OPTION_LONG,
						 alist.aopt[i].option,
						 alist.aopt[i].body);
		}
	}
}

arg_list arg_list_parse(int argc, char** argv) {
	arg_list alist = (arg_list){0,0,0};
	char** args = argv + 1;// remove program name
	int nargs = argc - 1;  // remove program count
	char is_first = 0;     // used in processing

	if (nargs < 1)         // if nargs not [1,+Inf)
		goto BadCall;
	
	alist = arg_list_heap_allocate(nargs);
	if (!alist.aopt)       // If failed to allocate return
		goto BadCall;

	int option_count = 0;
	for (int i = 0; i < nargs ; ) {
		char* option = read_option(&alist.aopt[option_count], args[i]);
		int steps = 0;

		if (option) {
			// Assumption: Logical AND shortcut behavior
			// if [next] is <i+1 < nargs> AND <not option>
			char* value = (((i+1)<nargs)&&read_option(NULL,args[i+1])==NULL) ?
				args[i+1]
				: NULL;
			steps = (value) ? 2 : 1;
			alist.aopt[option_count].option = option;
			alist.aopt[option_count].body = value;
		} else {
			steps = 1;
			alist.aopt[option_count].option = NULL;
			alist.aopt[option_count].body   = args[i];
		}

		i += steps;
		option_count++;
	}

	arg_list_adjust_noption(&alist, option_count); // adjust

	BadCall:
	return alist;
}
