import numpy as np
import cv2
import math

def segmentation(img, limiar):
    new_img = np.empty( (img.shape) )

    for y in xrange(new_img.shape[0]):
        for x in xrange(new_img.shape[1]):
            flag = True
            for z in xrange(new_img.shape[2]):
                flag = flag and img[y][x][z] > limiar[z]


            new_img[y][x] = img[y][x] if flag else 0

    return new_img

def main():
    limiar = 80

    image = cv2.imread("Images/laranjas.jpg")

    nuevo = segmentation(image, [200, 0, 0])

    cv2.imshow("original de verdade, a outra eh prank", image)
    cv2.imshow("original, prank", nuevo)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__": main()
