import numpy as np
import cv2

def locais(image, n, m):
    newImg = np.zeros(image.shape, dtype = np.uint8)

    vSize = image.shape[0]//n
    hSize = image.shape[1]//m

    for starty in xrange(n):
        for startx in xrange(m):
            window = image[starty*vSize:(starty+1)*vSize, startx*hSize:(startx+1)*hSize]
            break
        break

    return window


def main():
    imageru = cv2.imread('Images/coins.bmp', 0)
    n = 2 # vertical
    m = 3 # horizontal

    novo = locais(imageru, n, m)





    cv2.imshow("original", imageru)
    cv2.imshow("novo", novo)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__": main()
