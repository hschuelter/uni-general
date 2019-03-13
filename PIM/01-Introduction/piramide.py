import numpy as np
import im

img = im.read('cameraman.png')
dim = img.shape

n = m = 32

img2 = np.zeros((n,m), dtype = np.uint8)

salto = dim[1] // n

for i in range(0, dim[1], salto):
    for j in range(0, dim[2], salto):
        img2[i // salto][j // salto] = img[0][i][j]

im.show(img2)
