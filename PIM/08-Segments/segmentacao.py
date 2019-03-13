import numpy as np
import cv2

def segmentation(img, mascara, limiar):
    new_img = np.empty( (img.shape) )

    for y in xrange(1, new_img.shape[0] - 1):
        for x in xrange(1, new_img.shape[1] - 1):
            a = 0
            for yy in xrange(-1,2):
                for xx in xrange(-1,2):
                    a += img[y + yy][x + xx]*mascara[1 + yy][1 + xx]
            if a > limiar:
                new_img[y][x] = 255
            else:
                new_img[y][x] = 0

    return new_img




def main():
    limiar = 120
    hori = np.array( [[-1, -1, -1],
                      [ 2,  2,  2],
                      [-1, -1, -1]])

    vert = np.array( [[-1,  2, -1],
                      [-1,  2, -1],
                      [-1,  2, -1]])

    image = cv2.imread("Images/mandril.jpg", 0)
    image = cv2.copyMakeBorder(image, 1,1,1,1, cv2.BORDER_CONSTANT, 0)

    jetx = segmentation(image, hori, limiar)
    jety = segmentation(image, vert, limiar)

    cv2.imshow("original de verdade, a outra eh prank", image)
    cv2.imshow("AAAAX", jetx)
    cv2.imshow("AAAAY", jety)
    cv2.imshow("original", np.add(jetx, jety))
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__": main()
