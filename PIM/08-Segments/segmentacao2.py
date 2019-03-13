import numpy as np
import cv2
import math

def logaritmo(img):
    a = 255/(255**(1/2))
    new_img = np.empty( (img.shape) )

    for y in xrange(0, new_img.shape[0]):
        for x in xrange(0, new_img.shape[1]):
            new_img[y][x] = a*(img[y][x]**(1/2))

    return new_img

def segmentation(img, limiar):
    new_img = np.empty( (img.shape) )

    for y in xrange(1, new_img.shape[0] - 1):
        for x in xrange(1, new_img.shape[1] - 1):
            a = 0
            a += img[y][x]
            if a > limiar:
                new_img[y][x] = 255
            else:
                new_img[y][x] = 0

    return new_img




def main():
    limiar = 80
    hori = np.array( [[-1, -1, -1],
                      [ -1,  8,  -1],
                      [-1, -1, -1]])

    image = cv2.imread("Images/coins.bmp", 0)

    jetx = segmentation(image, limiar)

    cv2.imshow("original de verdade, a outra eh prank", image)
    cv2.imshow("AAAAX", jetx)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__": main()
