def cal_one_file(file_path):
    file = open(file_path, mode='r')
    lines = file.readlines()
    val = ''
    
    res = 0
    for val in lines:
        res += int(val)

    return float(res) / len(lines)

def create_fig(plt, xlist, ylist, access_name, name, tar_dir):
    #refresh plt
    plt.figure()

    #get max y value
    y_max = max(ylist[0])
    if y_max <= max(ylist[1]):
        y_max = max(ylist[1])

    plt.ylim(0, y_max + (y_max / 10) )

    #create
    plt.title(access_name + " access")
    plt.plot(xlist, ylist[0], '-d', label=name[0])
    plt.plot(xlist, ylist[1], '-s', label=name[1])

    plt.legend()#print the label for each data line

    # plt.show()

    plt.savefig(tar_dir + access_name + ".png")

    print(access_name + "fig created")
