import os
import math
import random
import numpy as np
import matplotlib.pyplot as plt

def sa_MEAN(file_path):

    sa = []
    for i in range(0, 10):
        file_info = open(file_path + 'sa-best-' + str(i) + '.data', 'r')
        file_info = file_info.read().split('\n')

        for j in range(0, len(file_info)-1):
            sa.append( int(file_info[j].split()[0]) )

    print(file_path)
    print("> ", end="")
    print(np.mean(sa), end="")

    print(" +- ", end="")
    print(np.std(sa))
    print()


def rs_MEAN(file_path):

    rs = []
    for i in range(0, 10):
        file_info = open(file_path + 'random-best-' + str(i) + '.data', 'r')
        file_info = file_info.read().split('\n')

        for j in range(0, len(file_info)-1):
            rs.append( int(file_info[j].split()[0]) )

    print(file_path)
    print("> ", end="")
    print(np.mean(rs), end="")

    print(" +- ", end="")
    print(np.std(rs))
    print()




def main():
    rs = []
    sa = []

    high_sa = './Data/high/SA/'
    low_sa  =  './Data/low/SA/'
    # SA #
    sa_MEAN(low_sa +  'uf20-01/')
    sa_MEAN(low_sa + 'uf100-01/')
    sa_MEAN(low_sa + 'uf250-01/')

    sa_MEAN(high_sa +  'uf20-01/')
    sa_MEAN(high_sa + 'uf100-01/')
    sa_MEAN(high_sa + 'uf250-01/')

    print("===========")

    # RS #
    high_rs = './Data/high/RS/'
    low_rs  =  './Data/low/RS/'
    
    rs_MEAN(low_rs +  'uf20-01/')
    rs_MEAN(low_rs + 'uf100-01/')
    rs_MEAN(low_rs + 'uf250-01/')

    rs_MEAN(high_rs +  'uf20-01/')
    rs_MEAN(high_rs + 'uf100-01/')
    rs_MEAN(high_rs + 'uf250-01/')


if __name__ == "__main__": main()