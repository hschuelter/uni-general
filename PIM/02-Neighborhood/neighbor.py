import numpy as np
import cv2

positions = [(-1,0), (0,-1), (1,0), (0,1), (-1,-1), (-1,1), (1,-1), (1,1)]

def viziVonNeumann(pixel, img, x, y): # 4 tiles around
	
	if pixel != img[y][x]:
		return False

	for k in range(0,4):
		i, j = positions[k]

		if pixel == img[y + j][x + i]:
			return False

	return True

def viziMoore(pixel, img, x, y): # 8 tiles around 
	
	if pixel != img[y][x]:
		return False


	for k in range(0, 8):
		i, j = positions[k]

		if pixel == img[y + j][x + i]:
			return False

	return True

def dotCounter(img, color):
	color4 = 0
	color8 = 0

	for i in range(0,img.shape[0]):
		for j in range(0, img.shape[1]):

			if 	viziVonNeumann(color, img, j, i):
				color4 += 1
			
			if viziMoore(color, img, j, i):
				color8 += 1


	
	return color4, color8

	

img = cv2.imread('imagens/ruidoBin.png',0)
img = cv2.copyMakeBorder(img, 1,1,1,1, cv2.BORDER_CONSTANT, -1)

black4, black8 =  dotCounter(img, 0)
white4, white8 =  dotCounter(img, 255)

print "\nVizinhanca de Von Neumann:"
print "\tBlack: " + str(black8)
print "\tWhite: " + str(white8) + "\n"

print "Vizinhanca de Moore: "
print "\tBlack: " + str(black4)
print "\tWhite: " + str(white4)


#cv2.imshow('ruido', img)
#cv2.waitKey(0)
#cv2.destroyAllWindows()