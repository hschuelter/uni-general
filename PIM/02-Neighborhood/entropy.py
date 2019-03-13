import numpy as np
import cv2


def entropy(img):

	cont = np.zeros(256)
	size = float(img.size)
	entro = 0

	for i in range(0, img.shape[0]):
		for j in range(0, img.shape[1]):
			cont[ img[i][j] ] += 1/size


	for i in cont:
		if i != 0:
			entro -= i * np.log2(i)

	return entro


img = cv2.imread('imagens/mandril.png',0) # mandril.jpg, lena.jpg, r-x.jpg, nature.jpg, base-erosao.png

print entropy(img)

