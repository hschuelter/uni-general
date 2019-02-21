import matplotlib.pyplot as plt
import numpy as np
#------------------------

_file  = open("histo.txt", "r")

histo = _file.read().splitlines()
histo = [map(int, x) for x in histo]
data = []

for i in histo:
	num = 0
	for j in xrange(0, len(i)):
		num = num*10 + i[j]
	data.append(num)

#print data


#-----------------------------
p1 = plt.bar(range(0,1000), data, color = 'purple')
plt.title('Colisoes de Hash')
plt.xlabel('Numero Hash')
plt.ylabel('Frequencia de Colisao')


#plt.xticks( x )
plt.yticks( np.arange(0, 501, 50) )
plt.grid(True)
#plt.legend(p1[0])


plt.show()
