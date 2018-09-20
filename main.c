#include <stdio.h>
#include <time.h>
#include <inttypes.h>

#include "mm.h"
#include "mb_node.h"

#define NB_NODES 32
#define CS_LEV 2

uint64_t time_measure(struct mb_node *nodes, int nodes_nb){
    struct timespec begin, end;
    uint64_t dura = 0;
    int i = 0;
    uint64_t temp;

    clock_gettime(CLOCK_REALTIME, &begin);

    //target code
    for(i = 0; i < nodes_nb; i++){
        temp = nodes[i].internal;
        nodes[i].internal = i;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    dura = ((int64_t)end.tv_sec*1000000000 + end.tv_nsec) 
           -((int64_t)begin.tv_sec*1000000000 + begin.tv_nsec);//ns

}

int main(int argc, char ** argv)
{
    struct mm mm_test;
    struct mb_node * nodes = NULL;
    uint64_t ret = 0;
    
    //init mem_op
    mm_init(&mm_test, MEM_ALLOC_COLOR);

//    //profile for test
//    mm_test.op->mm_profile(&mm_test);

    //alloc test
    nodes = mm_test.op->alloc_node(&mm_test, NB_NODES, CS_LEV);
    if(nodes != NULL){
        printf("alloc done\n");

        ret = time_measure(nodes, NB_NODES);

        printf("%d nodes r/w test : %lu ns\n", NB_NODES, ret);
    }
    else{
        perror("alloc fail");
        goto ALLOC_ERROR;
    }

   //dealloc
   mm_test.op->dealloc_node(&mm_test, NB_NODES, CS_LEV, nodes);

ALLOC_ERROR:

    //uint mem_op
    mm_uinit(&mm_test);

    return 0;
}