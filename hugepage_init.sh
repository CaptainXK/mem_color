#! /bin/bash

huge_mnt_path="/mnt/huge"

#test if dir exit
if [ ! -x $huge_mnt_path ]
then
	mkdir $huge_mnt_path
fi

#mnt dir with hugepage file system
mount -t hugetlbfs nodev "$huge_mnt_path"

#set count of hugae page
hugepage_nb=0
echo "input number of hugepage you want:"
read hugepage_nb

echo ${hugepage_nb} > /proc/sys/vm/nr_hugepages