import numpy as np
import sys

def diff_model(data_1, data_2, max_diff):
    data = np.absolute(data_1 - data_2)
    cur_max = np.max(data)

    if max_diff < cur_max :
        exit(-1)

if __name__ == "__main__":

    if len(sys.argv) < 3:
        print("+----------------------------+")
        print("Parameters: ")
        print("  Path to first binary data")
        print("  Path to second binary data")
        print("  Maximinium difference in p")
        print("+----------------------------+")
        exit(-1)

    data1 = np.fromfile(sys.argv[1], dtype=np.float64)
    data2 = np.fromfile(sys.argv[2], dtype=np.float64)
    max_diff = float(sys.argv[3])
    if len(sys.argv) == 5 :
        can_save = sys.argv[4]
    diff_model(data1, data2, max_diff)
