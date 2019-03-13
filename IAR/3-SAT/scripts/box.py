import os
import math
import random
import argparse
import numpy as np
import matplotlib.pyplot as plt

# === SETTING UP === #
def setup(filepath, random_path, schedule):   

    fit_info = open(filepath + 'sa-best-' + str(schedule) + '.data', 'r')
    fit_info = fit_info.read().split('\n')
    fitness = []

    random_info = open(random_path + 'random-best-' + str(schedule) + '.data', 'r')
    random_info = random_info.read().split('\n')
    rand_result = []
    
    for i in range(0, len(fit_info)-1):
        # print(fit_info[i])
        fitness.append( int(fit_info[i].split()[0]) )

    for i in range(0, len(random_info)-1):
        rand_result.append( int(random_info[i].split()[0]) )

    return fitness, rand_result
    
def single_box(file_, schedule, data):

    file_path = 'charts/' + file_ + '/SCH-' + str(schedule) + '/'
    file_name = 'single-box.png'

    fig, ax = plt.subplots()
    ax.set_title("Comparação (Schedule " + str(schedule) + ")")
    ax.boxplot(data)


    ax.yaxis.grid(True)
    ax.set_ylabel('Cláusulas')
    ax.set_xlabel('Algoritmo')

    plt.setp(ax, xticklabels = ['Simulated Annealing', 'Random Search'])
    # plt.show()
    

    if not os.path.exists(file_path):
        os.makedirs(file_path)
    
    fig.savefig(file_path + file_name)

def multiple_box(file_, data):

    label = []
    for i in range(0, 10):
        label.append('SA')
        label.append('RS')

    file_path = 'charts/' + file_ + '/'
    file_name = 'all-box.png'

    fig, ax = plt.subplots()
    ax.set_title("Comparação Geral")
    ax.boxplot(data)

    ax.yaxis.grid(True)
    ax.set_ylabel('Cláusulas')
    ax.set_xlabel('Algoritmo')

    plt.setp(ax, xticklabels = label)
    # plt.show()
    

    if not os.path.exists(file_path):
        os.makedirs(file_path)
    
    fig.savefig(file_path + file_name)

def main(file_):
    file_path = './output/SA/' + file_ + '/'
    random_path = './output/RS/' + file_ + '/'


    all_data = []
    for sch in range(0, 10):
        data = []
        fitness, rand_result = setup(file_path, random_path, sch)
        data.append(fitness)
        data.append(rand_result)

        single_box(file_, sch, data)

        all_data.append(fitness)
        all_data.append(rand_result)
        
    multiple_box(file_, all_data)
    
    # plot_chart_SA(fitness, temperature, rand_result, file_, schedule)
    # plot_chart_RS(fitness, temperature, rand_result, file_, schedule)
    # plot_mix_chart(fitness, temperature, rand_result, file_, schedule)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Charts")

    parser.add_argument('--file', '-f',
                        type=str,
                        help="Escolha o arquivo",
                        default="uf20-01")

    args = parser.parse_args()
    main(args.file)
