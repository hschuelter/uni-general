import numpy as np
import math as m
import cv2

def sqrtImg(img):
    new_img = np.zeros((img.shape[0], img.shape[1]), np.uint8)
    f_max = findMax(img)

    a = 255 / m.sqrt(f_max)

    for y in range(0, img.shape[0]):
        for x in range(0, img.shape[1]):
            new_img[y][x] = m.sqrt(img[y][x]) * a

    return new_img

def logImg(img):
    new_img = np.zeros((img.shape[0], img.shape[1]), np.uint8)
    f_max = findMax(img)

    a = 255 / m.log10(f_max + 1)

    for y in range(0, img.shape[0]):
        for x in range(0, img.shape[1]):
            new_img[y][x] = m.log10(img[y][x] + 1) * a

    return new_img

def findMax(img):
    f_max = 0

    for y in range(0, img.shape[0]):
        for x in range(0, img.shape[1]):
            if f_max < img[y][x]:
                f_max = img[y][x]

    return f_max


def main():
    
    img = cv2.imread('Images/foto-escura.jpg', 0)
    img = cv2.resize(img, (0,0), fx = 0.5, fy = 0.5)

    sImg = sqrtImg(img)
    lImg = logImg(img)

    cv2.imshow('Original', img)
    cv2.imshow('SQRT Woah', sImg)
    cv2.imshow('Log Woah', lImg)
    cv2.waitKey(0)

    print(lImg)

if __name__ == "__main__": main()
