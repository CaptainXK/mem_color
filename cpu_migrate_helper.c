#define _GNU_SOURCE
#include "cpu_migrate_helper.h"
#include <sched.h>//sched_***
#include <stdio.h>//stderr
#include <sys/types.h>
#include <unistd.h>//getpid()


int cpu_migrate(int tar_cpu)
{
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(tar_cpu, &cpu_set);

    if( sched_setaffinity(getpid(), sizeof(cpu_set), &cpu_set) != 0 ){
        return 1;
    }


    return 1;
}