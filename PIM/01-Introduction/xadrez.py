import numpy as np
import im

def GeraTabuleiro(W,H,T):

    numeroQuadrados = W/T

    img = np.zeros((W,H), dtype = np.uint8)

    print img
    ni = nj = 0

    for i in range(0, W, T):
        ni += 1
        for j in range(0, W, T):
           nj += 1
           for k in range(i, i+T):
               for l in range(j, j+T):
                    img[k][l] = ((ni+nj)%2) * 255

    return img


tabu = GeraTabuleiro(256, 256, 64)
print tabu
im.show(tabu)
