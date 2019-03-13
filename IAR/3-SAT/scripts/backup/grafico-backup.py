import os
import math
import random
import argparse
import numpy as np
import matplotlib.pyplot as plt

# === SETTING UP === #
fit_info = open('./output/fitness', 'r')
fit_info = fit_info.read().split('\n')
fitness = []

temp_info = open('./output/temperature', 'r')
temp_info = temp_info.read().split('\n')
temperature = []

temp_i = float(temp_info[0].split()[0])
tot_clau = int(fit_info[0].split()[0])

for i in range(1, len(fit_info)-1):
    # print(fit_info[i])
    fitness.append( int(fit_info[i].split()[0]) )
    temperature.append( float(temp_info[i].split()[0]) )


# Normalizing temperature
for i in range(0, len(temperature)):
    temperature[i] = 100.0 * temperature[i] / temp_i
    fitness[i] = 100.0 * float(fitness[i]) / tot_clau


label = np.arange( len(fitness) )

# print(fitness)
# print(temperature)
# print(label)


# === PLOTING === #

plt.title('Simulated Annealing')

# plt.plot(label, temperature, '-r', label = 'Temperatura')
plt.plot(label, fitness, '-b', label = 'Fitness')

# plt.ylim(top = 101 )
# plt.ylim(bottom = 0 )

plt.xlim(left = 0 )

plt.ylabel('Resultado (%)')
plt.xlabel('Iterações')
plt.grid(True)

plt.legend(loc='center right')

plt.show()
