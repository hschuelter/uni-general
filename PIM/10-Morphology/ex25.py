import numpy as np
import cv2

def main():
    img = cv2.imread("Images/ruidoBin.png", 0)
    rect = cv2.getStructuringElement( cv2.MORPH_RECT, (3,3))
    crect = cv2.getStructuringElement( cv2.MORPH_RECT, (9,9))

    # img = cv2.morphologyEx(img, cv2.MORPH_OPEN,    rect)
    #
    # img = cv2.morphologyEx(img, cv2.MORPH_ERODE,    rect)
    img = cv2.morphologyEx(img, cv2.MORPH_ERODE,    rect)
    # img = cv2.morphologyEx(img, cv2.MORPH_CLOSE,   rect)
    # img = cv2.morphologyEx(img, cv2.MORPH_DILATE,   rect)
    img = cv2.morphologyEx(img, cv2.MORPH_DILATE,   crect)
    # img = cv2.morphologyEx(img, cv2.MORPH_DILATE,   rect)
    # img = cv2.morphologyEx(img, cv2.MORPH_OPEN,   rect)
    imG = cv2.morphologyEx(img, cv2.MORPH_CLOSE,   rect)
    #
    # img = cv2.morphologyEx(img, cv2.MORPH_OPEN,    rect)
    cv2.imshow('A', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__": main()
