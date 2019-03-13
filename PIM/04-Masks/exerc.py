import numpy as np
import cv2

def main():
    img = cv2.imread('mandril.jpg',0)

    img = np.array( img * 0.2 , np.uint8)

    # img = np.array(img * 10, np.uint8)

    cv2.imshow('Mandril', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__" : main()
