import numpy as np
import cv2
#
from Queue import Queue

positions = [(-1,-1), (0,-1), (1,-1), (-1,0), (1,0), (-1,1), (0,1), (1,1)]

def showImage(label, pos):
	name = 'componente-' + str(pos) + '.png'
	img = np.zeros(label.shape, np.uint8)

	for y in range (0, img.shape[0]):
		for x in range(0, img.shape[1]):
			if label[y][x] == pos:
				img[y][x] = 1

	for y in xrange(0,img.shape[0]):
		for x in xrange(0,img.shape[1]):
				img[y][x] *= 255

	cv2.imshow(str(pos), img)
	cv2.waitKey(0)
	#cv2.imwrite(name, img)

def findNext(label):
	for y in range(0,label.shape[0]):
		for x in range(0,label.shape[1]):
			if(label[y][x] == 0):
				return x, y

	return -1, -1

def colorirBFS(image, label, color, x, y, paint):
	fila = Queue()
	fila.put([x, y])

	while ( not fila.isEmpty() ):
		item = fila.pop()
		x = item[0]
		y = item[1]

		for k in range(0, 8):
			i, j = positions[k]
			if (image[y + j][x + i] == color and label[y + j][x + i] == 0):
				fila.put([x + i, y + j])
				label[y+j][x+i] = paint

	return label


def main():
	resp = Queue()

	img  = cv2.imread('componentes.png', 0)
	img = cv2.copyMakeBorder(img, 1,1,1,1, cv2.BORDER_CONSTANT, -1)
	label= np.zeros(img.shape, np.uint8)

	x, y = findNext(label)
	paint = 0

	while(x != -1):
		paint += 1
		color = img[y][x]
		label = colorirBFS(img, label, color, x, y, paint)
		resp.put(label)

		x, y = findNext(label)

	print( str(paint) + ' componentes!' )

	position = 1
	while( not resp.isEmpty() ):
		showImage(resp.pop(), position)
		position += 1


if __name__== "__main__": main()
