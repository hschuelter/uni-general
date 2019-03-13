import numpy as np
import cv2

def binariza(img, treshold):
    new_img = np.zeros((img.shape[0], img.shape[1]), np.uint8 )

    for y in range(0, img.shape[0]):
        for x in range(0, img.shape[1]):
            if img[y][x] < treshold:
                new_img[y][x] = 0
            else:
                new_img[y][x] = 255

    return new_img


def main():
    img = cv2.imread('Images/mandril.jpg',0)
    img2 = binariza(img, 120)


    cv2.imshow('image', img2)
    cv2.waitKey(0)

if __name__== "__main__": main()
