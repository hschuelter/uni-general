import numpy as np
import cv2


def main():
    img = cv2.imread('Images/noise.png',0)
    lena = cv2.imread('Images/lena.jpg', 0)
    new_img = np.zeros((img.shape[0], img.shape[1]), np.uint8)

    cv2.medianBlur(img, 3, new_img)

    cv2.imshow('Median', new_img)
    cv2.imshow('Noise', img)
    cv2.imshow('Lena', lena)
    cv2.waitKey(0)

if __name__ == "__main__": main()
