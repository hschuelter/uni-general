import numpy as np
import cv2

def main():
    img = cv2.imread("Images/bolas2.bmp", 0)

    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            img[x, y] = abs(img[x, y] - 255)


    ellipse = cv2.getStructuringElement( cv2.MORPH_ELLIPSE, (3,3))
    Bellipse = cv2.getStructuringElement( cv2.MORPH_ELLIPSE, (7,7))
    rect = cv2.getStructuringElement( cv2.MORPH_RECT, (2,2))
    cross = cv2.getStructuringElement( cv2.MORPH_CROSS, (2,2))

    img = cv2.morphologyEx(img, cv2.MORPH_OPEN,    ellipse)

    img = cv2.morphologyEx(img, cv2.MORPH_ERODE,    ellipse)
    img = cv2.morphologyEx(img, cv2.MORPH_ERODE,    ellipse)
    img = cv2.morphologyEx(img, cv2.MORPH_CLOSE,   ellipse)
    img = cv2.morphologyEx(img, cv2.MORPH_DILATE,   ellipse)
    img = cv2.morphologyEx(img, cv2.MORPH_DILATE,   ellipse)
    img = cv2.morphologyEx(img, cv2.MORPH_OPEN,   ellipse)
    imG = cv2.morphologyEx(img, cv2.MORPH_CLOSE,   ellipse)

    img = cv2.morphologyEx(img, cv2.MORPH_OPEN,    ellipse)


    cv2.imshow("Telinha", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__": main()
