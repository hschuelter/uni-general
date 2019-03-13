import numpy as np
import random
import cv2

positions = [(-1,0), (0,-1), (1,0), (0,1), (-1,-1), (-1,1), (1,-1), (1,1)]

def viziVonNeumann(pixel, img, x, y): # 4 tiles around

	for k in range(0,4):
		i, j = positions[k]

		if pixel == img[y + j][x + i]:
			return False

	return True

def noiseVonNeumann(img, number):

	noise = img

	for i in range(0,number):
		color = random.randint(0,1) * 255
		x = random.randint(0, noise.shape[0] - 2)
		y = random.randint(0, noise.shape[1] - 2)


		if viziVonNeumann(color, noise, x, y) == True:
			noise[y][x] = color
		else:
			i -= 1

	return noise

def viziMoore(pixel, img, x, y): # 8 tiles around

	for k in range(0, 8):
		i, j = positions[k]

		if pixel == img[y + j][x + i]:
			return False

	return True


def noiseMoore(img, number):

    noise = img
    i = 0

    while(i < number):
        i += 1
        color = random.randint(0,1) * 255
        x = random.randint(0, noise.shape[0] - 2)
        y = random.randint(0, noise.shape[1] - 2)


        if viziMoore(color, noise, x, y) == True:
            noise[y][x] = color
        else:
            i -= 1
    return noise

def main():
    number = 1000

    imgM = cv2.imread('Images/lena.jpg',0)
    imgM = cv2.copyMakeBorder(imgM, 1,1,1,1, cv2.BORDER_CONSTANT, -1)

    imgM  = noiseMoore(imgM, number)

    #newimg = imgM[1:imgM.shape[0] - 1][1:imgM.shape[1] - 1]

    newimg = np.empty( (imgM.shape[0]-2, imgM.shape[1]-2), np.uint8)
    for y in range(0, imgM.shape[0]-2):
        for x in range(0, imgM.shape[1]-2):
            newimg[y][x] = imgM[y+1][x+1]


    cv2.imshow('Moore', newimg)
    cv2.waitKey(0)

    cv2.imwrite('noise.png', newimg)

if __name__ == "__main__":  main()
