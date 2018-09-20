import numpy as np
import matplotlib.pyplot as plt

print("hello python\n")
# list = np.random.rand(4,4)
# print(list)
# print("\n")

plt.xlabel('Send Rate(Mbps)')
plt.ylabel('Receive(Mbps)')
# plt.title('Throughput')

a = plt.subplot(1,1,1)#backgroud color

plt.ylim=(0, 5)
x = [1048, 2097, 3145, 4194, 5243, 6291, 7339, 8388, 9437, 10479]

y1 = [1048, 2097, 3145, 4194, 5243, 6291, 7339, 8388, 9437, 10479]
y2 = [1048, 2097, 3145, 4194, 5208, 5210, 5210, 5208, 5210, 5208]
y3 = [1048, 2097, 3145, 4194, 5243, 6291, 7339, 8388, 9437, 10486]

hy1 = [1048, 2097, 3145, 4194, 5243, 6291, 7339, 8388, 9437, 10479]
hy2 = [724, 1038, 1311, 1633, 1730, 1738, 1739, 1740, 1741, 1735]
hy3 = [988, 1533, 1904, 2363, 2702, 3027, 3420, 3718, 4041, 4368]

rtt_y1 = [3.49, 2.46, 2.1, 2.37, 3.63, 3.66, 3.57, 3.8, 3.83, 3.86]
rtt_y2 = [2.89, 1.82, 1.51, 1.84, 2.08, 2.2, 2.33, 2.37, 2.41, 2.45]
# plt.bar(x1, y1, facecolor='red', width=3, label = 'FG-NET')
# plt.bar(x2, y2, facecolor='green', width=3, label = 'MORPH')
# plt.bar(x3, y3, facecolor='blue', width=3, label = 'CACD2000')

# plt.plot(x, y1, '-o', label = 'Line-rate')
plt.plot(x, rtt_y1, '-d', label = 'BBS')
plt.plot(x, rtt_y2, '-s', label = 'MBBS')

plt.legend()#print the label for each data line

plt.show()
