import os
import math
import random
import argparse
import numpy as np
import matplotlib.pyplot as plt

generations = ""

def setup(file_name):
    global generations

    result_info = open(file_name + '-div.data', 'r', encoding = 'UTF-8').read().split('\n')

    generations = int(result_info[0])
    result_info.pop(0)

    div = np.zeros(( generations ,), dtype=float)

    for i in range(0, generations):
        div[i] = float(result_info[i])

    return div

def plot_charts(div, file_name):
    size = len(div)

    large = 0
    for i in range(0, generations):
        if(large < div[i]):
            large = div[i]


    plt.ylim(0, large + 0.05)
    plt.xlim(0, size)

    plt.plot(div, color='blue')

    plt.grid(axis='both')
    plt.xlabel('Geração')
    plt.ylabel('Diversidade')
    plt.suptitle("Diversidade", fontsize = 16)
    plt.title("Titulo B", fontsize = 10, loc='left')
    plt.savefig(file_name + '-div.png')
    # plt.show()


def main(args):
    div = setup(args.file)
    plot_charts(div, args.file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Parâmetros para a criação de gráficos")

    parser.add_argument('--file', '-f',
                        type=str,
                        help="Título do arquivo de teste",
                        default="Roulette")

    args = parser.parse_args()
    main(args)
