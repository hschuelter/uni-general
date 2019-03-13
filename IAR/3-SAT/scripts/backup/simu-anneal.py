import os
import math
import random
import argparse
import numpy as np
import matplotlib.pyplot as plt

from datetime import datetime

# ------Global Variables------
variables = np.full(1, False)
best = (np.full(1, False), 0)

clauses = np.zeros( (1,1) )
statements = np.zeros( (1,1) )

temperature = -1
init_temp = -1
final_temp= -1
schedule = 1

num_it = -1

fitness = []
# ----------------------------

def setup(path, temp_i, temp_f, num, sch):
    global variables, clauses, statements, schedule
    global temperature, init_temp, final_temp, best, num_it

    random.seed(datetime.now())

    info = open(path)
    info = info.read().split("\n")

    temperature = float(temp_i)
    init_temp   = float(temp_i)
    final_temp  = float(temp_f)
    schedule = int(sch)

    nVar  = int(info[0].split()[0])
    nClau = int(info[0].split()[1])

    num_it = num

    variables = np.full( nVar, False)
    clauses = np.zeros( (nClau, 3), dtype = 'uint8, bool' )
    statements = np.zeros( nClau, dtype = 'bool' )

    for i in range(0, len(variables)):
        if(random.randint(0, 100) % 2 == 0):
            variables[i] = not variables[i]

    best = ( variables , 0)

    for i in range(0, nClau):
        statements[i] = False
        a = info[i+1].split()
        for j in range(0, 3):
            clauses[i, j][0] = abs(int(a[j]))
            if(int(a[j]) > 0):
                clauses[i, j][1] = True

    return nVar, nClau

def solve(start, it):
    global variables, clauses, statements, best
    global fitness

    old_variables = variables
    randomize()

    atual = 0
    for i in range(0, clauses.shape[0]):

        a1 = xor( variables[clauses[i,0][0] - 1], clauses[i,0][1] )
        a2 = xor( variables[clauses[i,1][0] - 1], clauses[i,1][1] )
        a3 = xor( variables[clauses[i,2][0] - 1], clauses[i,2][1] )

        statements[i] = (a1 or a2 or a3)
        if(a1 or a2 or a3):
            atual += 1

    if(best[1] < atual):
        best = (variables, atual)

    if(atual < start):
        delta = start - atual
        chance = np.exp( (-delta) / temperature)
        print(chance)

        # Chance de não trocar as variaveis da ultima iteração
        if( ( random.uniform(0,1) > chance) ):
            variables = old_variables
            atual = start

    if(it % 2 == 0):
        fitness.append(atual)

    chance = cooldown(it)

    return atual

def randomize():
    global variables
    random.seed(datetime.now())

    nVar = len(variables)

    var = np.full(nVar, False)

    for i in range(0, nVar):
        if(random.uniform(0,1) < 0.01):
            variables[i] = not variables[i]

def cooldown(curr_it):
    global init_temp, final_temp, temperature, schedule, num_it

    new_temp = 0.0

    # Schedule 0
    if( schedule == 0 ):
        new_temp = temperature - ( float(init_temp / num_it) )

    # Schedule 1
    elif(schedule == 1):
        new_temp = init_temp * pow(( final_temp / init_temp), (curr_it / num_it))

    # Schedule 5
    elif(schedule == 5):
        new_temp = (0.5) * (init_temp - final_temp) * (1 + math.cos( (math.pi * curr_it)/num_it ) ) + final_temp

    temperature = new_temp

def main(args):
    global best, temperature, init_temp, num_it, fitness
    os.system('clear')

    path = "input/"
    _file= args.file

    nvar, nclau = setup(path + _file, args.temp_i, args.temp_f, args.number, args.schedule)

    print ("Numero de variaveis: " +  str(nvar))
    print ("Numero de clausulas: " + str(nclau))
    print ("Temperatura inicial: " + str(temperature))
    print ("=== ")

    ans = solve( best[1], 0)
    cont = 1
    while(num_it > cont):
        ans = solve(ans, cont)
        cont += 1

    fitness[ len(fitness) - 1 ] = best[1]


    # --- PRINT FINAL --- #

    print("Best: ", end="")
    normal_print(nclau)
    print("Iteracoes = " + str(cont))
    plotation(nvar)

    # ------------------- #

def normal_print(nClau):
    global best, fitness

    print( str(100 * best[1] / nClau)[0:5] + " %", end = " " )
    print("(" + str(best[1]) + "/" + str(nClau) + ")")
    # print(len(best[0]))

def plotation(num):
    global fitness, clauses

    plt.title('Simulated Annealing')

    label = np.arange( len(fitness) )
    plt.plot(label, fitness)

    # plt.ylim(top = 451 )
    # plt.ylim(bottom = 0 )

    plt.ylabel('Fitness')
    plt.xlabel('Iterações')
    plt.grid(True)

    plt.show()

def xor(a, b):
    return (not ( a ^ b ))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Simulated Annealing")

    parser.add_argument('--file', '-f',
                        type=str,
                        help="Escolha o arquivo",
                        default="uf20-01.in")

    parser.add_argument('--temp_i', '-ti',
                        type=float,
                        help="Temperatura inicial",
                        default=100.0)

    parser.add_argument('--temp_f', '-tf',
                        type=float,
                        help="Temperatura final",
                        default=1.0)

    parser.add_argument('--number', '-n',
                        type=int,
                        help="Numero de iterações",
                        default=100000)

    parser.add_argument('--schedule', '-s',
                        type=int,
                        help="Tipo de resfriamento",
                        default=0)

    args = parser.parse_args()
    main(args)
