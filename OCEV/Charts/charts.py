import os
import math
import random
import argparse
import numpy as np
import matplotlib.pyplot as plt

title = ""
selection = ""
crossover = ""
mutation = ""
cross_chance = ""
mut_chance = ""
elitism = ""
generations = ""

def setup(file_name):
    global selection, crossover, mutation, cross_chance, mut_chance, elitism, generations, title

    result_info = open(file_name, 'r', encoding = 'UTF-8').read().split('\n')

    title = result_info[0]
    selection = result_info[1]
    crossover = result_info[2]
    mutation = result_info[3]
    cross_chance = result_info[4]
    mut_chance = result_info[5]
    elitism = result_info[6]
    generations = int(result_info[7])

    for i in range(0,8):
        result_info.pop(0)

    # print("Selection: " + selection)
    # print("Crossover: " + crossover)
    # print("Mutation: " + mutation)
    # print("Crossover Chance: " + cross_chance)
    # print("Mutation Chance: " + mut_chance)
    # print("Elitismo: " + elitism)
    # print("Generations: " + str(generations))

    bests  = np.zeros(( generations ,), dtype=float)
    worsts = np.zeros(( generations ,), dtype=float)
    average = np.zeros(( generations ,), dtype=float)

    for i in range(0, generations):
        result_info.remove("")

    for i in range(0, generations):
        bests[i]   = float(result_info[3*i])
        average[i] = float(result_info[3*i + 1])
        worsts[i]  = float(result_info[3*i + 2])

    return bests, average, worsts

def plot_charts(best, average, worst, file_name):
    best_point = (-1, -1)
    _title = selection + ' (' + elitism + ')'

    file_name = file_name[9:]

    size = len(best)

    for i in range(0, size):
        if best_point[1] < best[i]:
            best_point = (i, best[i])

    plt.ylim(0, 1.06)
    plt.xlim(0, size)

    ponto = "(" + str(best_point[0]) + ', ' + str(best_point[1]) + ')'
    if(best_point[0] < (size * 0.84) ):
        texto_x = best_point[0]
    else:
        fix = ((size * 0.84) - best_point[0])/size
        texto_x = best_point[0] + fix*size

    texto_y = best_point[1]+0.01

    plt.plot(best, color='blue', label="Melhor")
    plt.plot(average, color='black', label="Média")
    plt.plot(worst, color='red', label="Pior")
    plt.scatter(best_point[0], best_point[1], s = 100)
    plt.text(texto_x, texto_y + 0.02, ponto, fontsize=9)

    plt.legend(loc='center right', shadow=True, fontsize=10)

    plt.grid(axis='both')
    plt.xlabel('Geração')
    plt.ylabel('Fitness')
    plt.suptitle(title, fontsize = 16)
    plt.title(_title, fontsize = 10, loc='left')
    plt.savefig('./Charts/' + file_name[:len(file_name)-4] + '.png')
    # plt.show()


def main(args):
    best, average, worst = setup(args.file)
    plot_charts(best, average, worst, args.file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Parâmetros para a criação de gráficos")

    parser.add_argument('--file', '-f',
                        type=str,
                        help="Título do arquivo de teste",
                        default="Roulette")

    args = parser.parse_args()
    main(args)
