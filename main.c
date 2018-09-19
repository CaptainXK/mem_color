#include <stdio.h>

#include "mm.h"

int main(int argc, char ** argv)
{
    struct mm mm_test;
    
    //init mem_op
    mm_init(&mm_test, MEM_ALLOC_COLOR);

    //init mm
    mm_test.op->init(&mm_test);

    //profile for test
    mm_test.op->mm_profile(&mm_test);

    //uinit mm
    mm_test.op->uinit(&mm_test);

    //uint mem_op
    mm_uinit(&mm_test);

    return 0;
}