#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <sched.h>//sched_getcpu()

#include "mm.h"
#include "mb_node.h"
#include "cpu_migrate_helper.h"

int CS_LEV[3] = {0, 1, 2};
int NB_NODES[3] = {32, 32, 32};
int TEST_ROUND = 1024;
int VISIT_MODE = 0;
int ALLOC_TYPE = 0;
int DEBUG_OUT = 0;
int DO_MIGRATE = 0;
int TAR_CPU = 0;

//command line helper
void cmd_helper()
{
    printf("Command Line Helper\n");
    printf("\t-c:\ttest rounds, default value is 1024\n");
    printf("\t-t:\tpage allocator type,\"0\" for simple, \"1\" for coloring, default value is 0\n");
    printf("\t-m:\tvisit mode, \"0\" for contiguous access, \"1\" for random access, default value is 0\n");
    printf("\t-n:\tnumber of nodes for each color lma, default value is 32, 32, 32\n");
    printf("\t-M:\tmigrate to given cpu\n");
    printf("\t-D:\tDEBUG output mode, \"0\" for close status, \"1\" for open status, default value is 0\n");
    return;
}

//command line parse
int parse_cmd(int argc, char** argv)
{
    int opt;

    while( (opt = getopt(argc, argv, "c:t:m:n:M:Dh")) != -1 ){
        
        switch (opt)
        {
            case 'c':
                TEST_ROUND = (int)atoi(optarg);
                break;
            case 't':
                ALLOC_TYPE = (int)atoi(optarg);
                break;
            case 'm':
                VISIT_MODE = (int)atoi(optarg);
                break;
            case 'n':
                NB_NODES[0] = (int)atoi(optarg);
                NB_NODES[1] = (int)atoi(argv[optind]);
                NB_NODES[2] = (int)atoi(argv[optind + 1]);
                break;
            case 'M':
                DO_MIGRATE = 1;
                TAR_CPU = (int)atoi(optarg);
                break;
            case 'D':
                DEBUG_OUT = (int)1;
                break;
            case 'h':
            default:
                cmd_helper();
                return 1;
        }
    }

    return 0;
}

//time elapsed measurement
uint64_t time_measure(struct mb_node **nodes, int **visit_seq, int len)
{
    struct timespec begin, end;
    uint64_t dura = 0;
    int i = 0, j = 0;
    uint64_t temp;

    clock_gettime(CLOCK_REALTIME, &begin);

    //target code
    for(i = 0; i < 3; ++i){
        for(j = 0; j < len; ++j){
            temp = nodes[i][visit_seq[i][j]].data;
            nodes[i][visit_seq[i][j]].data = i;
        }
    }

    clock_gettime(CLOCK_REALTIME, &end);
    dura = ((int64_t)end.tv_sec*1000000000 + end.tv_nsec) 
           -((int64_t)begin.tv_sec*1000000000 + begin.tv_nsec);//ns
    
    return dura / (len * 3);
}

//create visit sequence, and each elem of this sequence is a id of data in nodes 
void sequence_create(int mode, int * array_var, int len, int nodes_nb)
{
    if(mode != 0 && mode != 1){
        printf("error visit sequence mode\n");
        exit(1);
    }

    if(mode == 1){
        if(DEBUG_OUT == 1)
            printf("Random access mode visit seq...\n");
        srand(time(NULL));
    }
    else{
        if(DEBUG_OUT == 1)
            printf("Contiguous access mode visit seq...\n");
    }
    
    for(int i=0; i<len; ++i){
        if(mode == 0)
            array_var[i] = i % nodes_nb;
        else
            array_var[i] = rand() % nodes_nb;
    }
}

int main(int argc, char ** argv)
{

    if( parse_cmd(argc, argv) != 0){
        return 0;
    }

    //check nodes number
    if(DEBUG_OUT == 1){
        printf("LV_1:%d, LV_2:%d, LV_3:%d\n", NB_NODES[0], NB_NODES[1], NB_NODES[2] );
    }

    //check do cpu migrate
    if(DO_MIGRATE == 1){
        assert( cpu_migrate(TAR_CPU) != 0);

        if(DEBUG_OUT == 1)
            printf("Current CPU is %d\n", sched_getcpu());
    }
    else{
        if(DEBUG_OUT == 1)    
            printf("Running on default CPU\n");
    }

    struct mm mm_test;
    struct mb_node * nodes[3] = {NULL, NULL, NULL};
    uint64_t ret = 0;
    int * visit_seq[3] = {NULL, NULL, NULL};
    
    //init visit_seq
    for(int i=0; i<3; ++i){
        visit_seq[i] = (int*)calloc(TEST_ROUND, sizeof(int));
        assert(visit_seq[i] != NULL);
        sequence_create(VISIT_MODE, visit_seq[i], TEST_ROUND, NB_NODES[i]);
    }

    //init mem_op
    if(DEBUG_OUT == 1){
        if(ALLOC_TYPE == MEM_ALLOC_SIMPLE)
            printf("Simple allocator...\n");
        else
            printf("Coloring allocator...\n");
    }
    mm_init(&mm_test, ALLOC_TYPE);

    //alloc
    for(int i=0; i<3; ++i){
        nodes[i] = mm_test.op->alloc_node(&mm_test, NB_NODES[i], CS_LEV[i]);
        assert(nodes[i] != NULL);
        if(DEBUG_OUT)
            printf("Nodes #%d alloc done\n", i);
    }

    //r/w test
    ret = time_measure(nodes, visit_seq, TEST_ROUND);

    if(DEBUG_OUT == 1)
        printf("%d Nodes %d times access: ", NB_NODES[0] + NB_NODES[1] + NB_NODES[2], TEST_ROUND * 3);

    printf("%lu", ret);

    if(DEBUG_OUT == 1)
        printf(" ns");

    printf("\n");

    //dealloc
    for(int i = 0; i<3; ++i){
        mm_test.op->dealloc_node(&mm_test, NB_NODES[i], CS_LEV[i], nodes[i]);
    }

ALLOC_ERROR:

    //uint mem_op
    mm_uinit(&mm_test);

    return 0;
}
