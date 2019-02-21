#import numpy as np

# Encontra a maior subsquência comum entre duas strings
def msc(X, Y):
    m = len(X)
    n = len(Y)
    
    M = [[0 for x in range(n+1)] for x in range(m+1)]

    for i in range(m+1):
        for j in range(n+1):
            # Popula a primeira e primera coluna com zeros
            if i == 0 or j == 0:
                M[i][j] = 0
            elif X[i-1] == Y[j-1]:
                M[i][j] = M[i-1][j-1] + 1
            else:
                M[i][j] = max(M[i-1][j], M[i][j-1])

    aux = M[m][n]
    msc = [""] * (aux+1)
    msc[aux] = ""

    auxX = ' ' + X
    auxY = '  ' + Y
    
    print (end=" ")
    for i in range(0, len(auxY)):  
        print(auxY[i] + "  ", end="")

    print()

    for i in range(0, len(auxX)):
        print(auxX[i] + ": ", end="")
        print(M[i])

    i = m
    j = n
    while i > 0 and j > 0:
        if X[i-1] == Y[j-1]:
            msc[aux-1] = X[i-1]
            i-=1
            j-=1
            aux-=1
        elif M[i-1][j] > M[i][j-1]:
            i-=1
        else:
            j-=1

    print ("A maior subsequência comum entre " + X + " e " + Y + " é " + "".join(msc))

genome = "ACCUGTATAUCGUCACTU"
feature = "GCAUTTC"
msc(genome, feature)
