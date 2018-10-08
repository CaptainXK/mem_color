import numpy as np
import matplotlib.pyplot as plt
import data_file_cal as dfc
import sys, getopt

def __usage__():
    print("usage:")
    print("\t-n:\tnumber of nodes")
    return

def __parse_cmd__(argv):
    try:
        opts, args = getopt.getopt(argv, "n:h")
    except getopt.GetoptError:
        __usage__()
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-n':
            NB_NODES_STR = arg
        elif opt == '-h':
            __usage__()

    return NB_NODES_STR

#parse cmd
PREFIX = __parse_cmd__(sys.argv[1:])

root_dir = "/home/xk/git/mem_color/"

test_round = range(1000, 11000, 1000)
access_mode_name = ['random','contiguous']
access_mode = [0,1]
alloc_mode_name = ['simple','color']
alloc_mode = [0,1]

rand_res = [[], []]
conti_res = [[], []]

for access_id, access_name in enumerate(access_mode_name):
    for alloc_id, alloc_name in enumerate(alloc_mode_name):
        for test_id, test_r in enumerate(test_round):

            # print("access mode:" + access_name + ", alloc mode:" + alloc_name + ", test round:" + str(test_r) )
  
            file_path = root_dir + "data/" + access_name + "_" + alloc_name + "_" + str(test_r) + "_data"
  
            ret = dfc.cal_one_file(file_path)

            # rand access mode
            if access_id == 0:
                rand_res[alloc_id].append(ret)
            else:
                conti_res[alloc_id].append(ret)

# print("conti simple:")
# print(conti_res[0])

# print("conti color:")
# print(conti_res[1])

# print("rand simple:")
# print(rand_res[0])

# print("rand color:")
# print(rand_res[1])


dfc.create_fig(plt, test_round, conti_res, access_mode_name[0], alloc_mode_name, root_dir + "fig/" + PREFIX + "_")
dfc.create_fig(plt, test_round, rand_res, access_mode_name[1], alloc_mode_name, root_dir + "fig/" + PREFIX + "_")
