import os
import math
import random
import argparse
import numpy as np
import matplotlib.pyplot as plt

# === SETTING UP === #
def setup(filepath, file_, schedule, it):   

    fit_info = open(filepath + 'fit/fitness-' + str(schedule) + '-' + str(it) + '.data', 'r')
    fit_info = fit_info.read().split('\n')
    fitness = []

    temp_info = open(filepath + 'tem/temperatura-' + str(schedule) + '-' + str(it) + '.data', 'r')
    temp_info = temp_info.read().split('\n')
    temperature = []

    file_random = './output/RS/' + file_ + '/random-'
    file_random+= str(schedule) + '-' + str(it) + '.data'
    random_info = open(file_random, 'r')
    random_info = random_info.read().split('\n')
    rand_result = []

    temp_i = float(temp_info[0].split()[0])
    tot_clau = int(fit_info[0].split()[0])
    tot_rand = int(random_info[0].split()[0])

    for i in range(1, len(fit_info)-1):
        # print(fit_info[i])
        fitness.append( int(fit_info[i].split()[0]) )

    for i in range(1, len(temp_info)-1):
        temperature.append( float(temp_info[i].split()[0]) )

    for i in range(1, len(random_info)-1):
        rand_result.append( float(random_info[i].split()[0]) )

    return fitness, temperature, rand_result
    
def plot_chart_SA(fitness, temperature, rand_result, file_, schedule):

    file_path = 'charts/' + file_ + '/SCH-' + str(schedule) + '/'
    file_name = 'convergencia-SA.png'

    fig, ax = plt.subplots(2,1)
    # fig, ax = plt.subplots(3,1)

    ax[0].plot(fitness, color='blue')
    ax[0].yaxis.grid(True)
    ax[0].set_xlabel('Iteração')
    ax[0].set_ylabel('Cláusulas')
    ax[0].set_title('Simulated Annealing')

    # ax[0].plot(rand_result, color='yellow')
    # ax[0].set_xlabel('Iteração')
    # ax[0].set_ylabel('Cláusulas')
    # ax[0].set_title('Busca Aleatória')


    ax[1].plot(temperature, color='red')
    ax[1].yaxis.grid(True)
    ax[1].set_xlabel('Iteração')
    ax[1].set_ylabel('Temperatura')
    ax[1].set_title('Temperatura')

    plt.tight_layout()
    # plt.show()

    if not os.path.exists(file_path):
        os.makedirs(file_path)
    
    fig.savefig(file_path + file_name)

def plot_chart_RS(fitness, temperature, rand_result, file_, schedule):

    file_path = 'charts/' + file_ + '/SCH-' + str(schedule) + '/'
    file_name = 'convergencia-RS.png'

    fig, ax = plt.subplots(1,1)

    plt.plot(rand_result, color='yellow')
    plt.gca().yaxis.grid(True)
    plt.xlabel('Iteração')
    plt.ylabel('Cláusulas')
    plt.title('Busca Aleatória')

    plt.tight_layout()
    # plt.show()

    if not os.path.exists(file_path):
        os.makedirs(file_path)
    
    plt.savefig(file_path + file_name)

def plot_mix_chart(fitness, temperature, rand_result, file_, schedule):

    file_path = 'charts/' + file_ + '/SCH-' + str(schedule) + '/'
    file_name = 'convergencia-0.png'

    fig, ax = plt.subplots(3,1)

    ax[0].plot(fitness, color='blue')
    ax[0].yaxis.grid(True)
    ax[0].set_xlabel('Iteração')
    ax[0].set_ylabel('Cláusulas')
    ax[0].set_title('Simulated Annealing')

    ax[1].plot(rand_result, color='yellow')
    ax[1].yaxis.grid(True)
    ax[1].set_xlabel('Iteração')
    ax[1].set_ylabel('Cláusulas')
    ax[1].set_title('Busca Aleatória')


    ax[2].plot(temperature, color='red')
    ax[2].yaxis.grid(True)
    ax[2].set_xlabel('Iteração')
    ax[2].set_ylabel('Temperatura')
    ax[2].set_title('Temperatura')

    plt.tight_layout()
    # plt.show()

    if not os.path.exists(file_path):
        os.makedirs(file_path)
    
    fig.savefig(file_path + file_name)

def main(file_, schedule):
    filepath = './output/SA/' + file_ + '/'


    fitness, temperature, rand_result = setup(filepath, file_, schedule, 0)        

    for it in range(1, 10):
        f, t, r= setup(filepath, file_, schedule, it)

        for j in range(0, len(fitness)):
            fitness[j] += f[j]

        for j in range(0, len(temperature)):        
            temperature[j] += t[j]

        for j in range(0, len(rand_result)):        
            rand_result[j] += r[j]

    for it in range(0, len(fitness)):
        fitness[it] /= 10.0

    for it in range(0, len(temperature)):
        temperature[it] /= 10.0

    for it in range(0, len(rand_result)):
        rand_result[it] /= 10.0
    
    plot_chart_SA(fitness, temperature, rand_result, file_, schedule)
    plot_chart_RS(fitness, temperature, rand_result, file_, schedule)
    plot_mix_chart(fitness, temperature, rand_result, file_, schedule)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Charts")

    parser.add_argument('--file', '-f',
                        type=str,
                        help="Escolha o arquivo",
                        default="uf20-01")

    parser.add_argument('--schedule', '-s',
                        type=int,
                        help="Tipo de resfriamento",
                        default=0)

    args = parser.parse_args()
    main(args.file, args.schedule)
