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

git clone repository
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
    `gcc -I argument_list_parse/include/ -o program program.c -L argument_list_parse/build/ -larglist`

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
## program.c
    #include "parse.h"
    int main(int argc, char** argv) {
        arg_list a = arg_list_parse(argc,argv);
        // use it a
        arg_list_heap_deallocate(&a);
        return 0;
    }

## notes
    - Calls recursion of `main(int,char**)` or any function using `arg_list_parse(int,argv**)` should use it in each call and its family
    or functions
    - If changes or a different argc, argv are used
    - remember to call `arg_list_heap_deallocate`

