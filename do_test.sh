#! /bin/bash

#test if test.app exsit
if ! test -e test.app
then
    echo "Error:test.app does not exsit, test terminated"
    exit
else
    echo "test.app check done"
fi

#initialize data foler
if ! test -d data
then
    echo "Create data folder"
    mkdir data
else
    echo "clean data folder"
    rm ./data/*
fi

#test control var
TEST_ROUND=(1000 2000 3000 4000 5000 6000 7000 8000 9000 10000)

ALLOC_MODE=(0 1)
ALLOC_MODE_NAME=('simple' 'color')

ACCESS_MODE=(0 1)
ACCESS_MODE_NAME=('conti' 'rand')

REPEAT=10
repeat_cur=0

#do test
for access_m in ${ACCESS_MODE[@]}
do
    for alloc_m in ${ALLOC_MODE[@]}
    do
        for test_r in ${TEST_ROUND[@]}
        do
            let "repeat_cur=0"
            echo "test round = ${test_r}, access mode = ${ACCESS_MODE_NAME[ $access_m ]}, alloc mode = ${ALLOC_MODE_NAME[ $alloc_m ]}"
            while (( $repeat_cur < $REPEAT ))
            do               
                echo "the $repeat_cur th test" 
                ./test.app -c $test_r -t $alloc_m -m $access_m >> ./data/${ACCESS_MODE_NAME[ $access_m ]}_${ALLOC_MODE_NAME[ $alloc_m ]}_${test_r}
                let "repeat_cur++"
            done
        done
    done 
done
