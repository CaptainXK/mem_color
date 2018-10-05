#! /bin/bash

huge_mnt_path="/mnt/huge"

#test if dir exit
if [ ! -x $huge_mnt_path ]
then
	mkdir $huge_mnt_path
fi

#mnt dir with hugepage file system
mount -t hugetlbfs nodev "$huge_mnt_path"

#read huge page size info
hugepagesize=`cat /proc/meminfo | grep -i hugepagesize | awk -F'[: ]+' '{print $2}'`
unit=`cat /proc/meminfo | grep -i hugepagesize | awk -F'[: ]+' '{print $3}'`

#set count of hugae page
hugepage_nb=0
echo "input number of hugepage you want (huge page size is ${hugepagesize}${unit}):"
read hugepage_nb

echo ${hugepage_nb} > /proc/sys/vm/nr_hugepages

#if you want umount huge
#cat /proc/mounts to check all hugetlbfs mount information
#umount all huge dir
#then rm them