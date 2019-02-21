import matplotlib.pyplot as plt
import numpy as np
#------------------------

insert_time = np.array([6.737, 51.805, 106.554, 201.537, 195.664])
search_time = np.array([2.224, 29.034,  31.133,  68.730, 197.631])
total_time  = insert_time + search_time

print(total_time)



n = 5
delta = 0.5
x = np.arange(n) + delta

wid = 0.26
p1 = plt.bar(x - wid/2, insert_time, width = wid, color = 'purple'    , align = 'center')
p2 = plt.bar(x + wid/2, search_time, width = wid, color = 'orangered' , align = 'center')

plt.title('Arvore Binaria')
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