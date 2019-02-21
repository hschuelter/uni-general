import matplotlib.pyplot as plt
import numpy as np
#------------------------

insert_time = np.array([6.627, 30.435, 50.211, 83.374,  83.354])
search_time = np.array([3.965, 28.679, 28.358, 83.234, 273.736])
total_time  = insert_time + search_time

print(total_time)



n = 5
delta = 0.5
x = np.arange(n) + delta

wid = 0.26
p1 = plt.bar(x - wid/2, insert_time, width = wid, color = 'purple'    , align = 'center')
p2 = plt.bar(x + wid/2, search_time, width = wid, color = 'orangered' , align = 'center')

plt.title('Lista com Hash')
plt.xticks(x, ('Teste 1', 'Teste 2', 'Teste 3', 'Teste 4', 'Teste 5'))
plt.yticks( np.arange(0, 301, 50) )
plt.ylabel("Tempo (ms)")
plt.grid(True)

plt.legend( (p1[0], p2[0]),
			('Insercao', 'Busca'),
			fancybox =  True, 
			shadow = True,
			loc = 'upper left')
plt.show()