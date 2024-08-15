@Developer: JOSIAH KUNDA MAPALO MALWELE  
@Name     : MALWELE   
@Email    : josiahkundamapalo@gmail.com  
            malwele085@gmail.com  
@Purpose  : Parsing program argument lists made easy  
@Licence  : GNU General Public Licence   

# ARGUMENT_LIST_PARSE
---
What you need  
    - linux (or unix based system)
    - make
    - gcc
    - ar

git clone malwele2004/argument_list_parse  
cd argument_list_parse  
make debug ** Make debug in build directory **  
make release ** Make libarglist.a in build directory **  

## TESTING
    make debug
    ./build/test arg_list

## DEPLOYMENT
    make release

## USE
    Include `parse.h` to your source code
    `gcc -I argument_list_parse/include/`
    Specify libarglist.a directory
    `gcc -L argument_list_parse/build/`
    Include it by using -l flag
    `gcc -larglist`
    Altogether
    `gcc -I argument_list_parse/include/ -o program program.c -L   argument_list_parse/build/ -larglist`

## DATA STRUCTURES
    <arg_option>
        1. <int>is_short
            Specifies whether option is short or long
            Ignore is no option, value is given
        2. <char*>option
            Option name, NULL if not given
        3. <char*>body
            Value name, NULL if not given
    <arg_list>
        1. <int>nargs
            Number of arguments given
        2. <int>noptions
            Number of options given
            Less than or equal nargs
        3. <arg_option*>
            Pointer to calloc allocated array
            of noptions Options
## Functions
    - Parse argument list (returns <arg_list>)
        arg_list_parse(<int>ArgumentCount,
                      <char**>ArgumentString,
                      <int>NumberOfLongArgumentsYouRecognised,
                     <char**>YourLongArguments)
    - Deallocate argument list (returns <void>)
        arg_list_heap_deallocate(arg_list*)

        Example
        -------
        ** ProgramA **
            source_files,i,install Option will take all arguments after them till end or another flag is found

        char* largs[] = {"--source_files","-i","--install"};
        int nlargs = 3;

        arg_list a = arg_list_parse(argc,argv,nlargs,largs);
        // Use arg_option
        printf("", a.aopt[0].option, a.aopt[0].body); // Print out first option
        arg_list_heap_deallocate(&a);

        ** ProgramB **

        arg_list a = arg_list_parse(argc, argv, 0, NULL)
        or
        arg_list a = arg_list_parse(argc, argv, X, NULL)
        or
        arg_list a = arg_list_parse(argc, argv, 0, X)

        // All don't supply long arguments
        // Use arg_list
        // Deallocate it

## notes
    - Calls recursion of `main(int,char**)` or any function using `arg_list_parse(int,char**,int,char**)` should use it in each call and its family
    or functions
    - If changes or a different argc, argv are used
    - remember to call `arg_list_heap_deallocate`
    - options supported --long or -short
    - use `noptions` to know how many arguments supplied, when indexing
     arg_list options array

## rules and precedence of flags
    1. Long arguments
    2. Long options
    3. Short options

If -o long argument exists
    -ogame is short option (ogame)
Else
    option (o), value(game)

If f long option and short option exist
    --f is long option
    -f is short option
