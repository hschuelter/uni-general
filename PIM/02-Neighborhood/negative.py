import numpy as np
import cv2

def negativate(img):
	neg_img = np.zeros((img.shape[0], img.shape[1], 3), np.uint8)

	for i in range(0, img.shape[0]):
		for j in range(0, img.shape[1]):
			for k in range(0,3):
				neg_img[i][j][k] = 255 - img[i][j][k]

	return neg_img


img = cv2.imread('imagens/mandril.jpg') # test with mandril-neg.jpg
img2 = negativate(img)


cv2.imshow('image', img2)
cv2.waitKey(0)
cv2.destroyAllWindows()
