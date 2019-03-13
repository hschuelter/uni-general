import numpy as np
import cv2
import matplotlib.pyplot as plt

def histo(img):
    hist = np.zeros( 256 )
    tot = img.shape[0] * img.shape[1]

    for y in range(0, img.shape[0]):
        for x in range(0, img.shape[1]):
            hist[ img[y][x] ] += 1.0
    return hist

def main():
    img = cv2.imread('Images/lena.jpg',0)
    hist = histo(img)

    plt.bar(range(0, 256), hist, facecolor = 'g', alpha=0.75)
    plt.title('Histogram')
    plt.grid(True)
    plt.show()

    #print (hist)

if __name__== "__main__": main()
