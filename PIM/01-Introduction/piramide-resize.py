import numpy as np
import cv2

def resize(original, dimension_x, dimension_y):
	x, y =  original.shape[0], original.shape[1]
	new_img = np.zeros( (dimension_x, dimension_y, 3) , np.uint8)

	xskip = x / dimension_x
	yskip = y / dimension_y

	for i in range(0, x, xskip):
		for j in range(0, y, yskip):
			new_img[i/xskip][j/yskip] = original[i][j]

	return new_img



img = cv2.imread('triforce.jpg')
img2 = resize(img,200,200)


cv2.imshow('Image', img2)
cv2.waitKey(0)
cv2.destroyAllWindows()