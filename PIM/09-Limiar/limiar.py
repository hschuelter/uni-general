import cv2
import numpy as np
import random
import math
import matplotlib as plt


def limiar(img, t, hL):
    newImg = np.zeros(img.shape, dtype=np.uint8)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            if hL:
                if img[i][j] > t:
                    newImg[i][j] = 255
            else:
                if img[i][j] <= t:
                    newImg[i][j] = 255


    return newImg


def average(img):
    return np.average(img)

def globalLimiar(img, limit):
    x = 28
    nuevo = x

    while True:
        x = nuevo
        print ('Testing limiar: ', x)

        m1 = average(limiar(img, x, True))
        m2 = average(limiar(img, x, False))

        print((m1,m2))

        nuevo = int((m1 + m2)//2)

        if abs(x-nuevo) <= limit:
            break

    return nuevo


def main():
    salada = cv2.imread('Images/coins.bmp', 0)
    histo, _ = np.histogram(salada, range(0,255))
    print (histo)

    suba = globalLimiar(salada, 1)
    print (suba)

    result = limiar(salada, suba, True)

    cv2.imshow('salada,', salada)
    cv2.imshow('result,', result)

    cv2.waitKey(0)
    cv2.destroyAllWindows()





if __name__ == "__main__": main()
