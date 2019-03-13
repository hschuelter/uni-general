import numpy as np
import cv2

def media(image, num):
    radius = num // 2

    new_img = np.empty(image.shape, np.uint8)

    for y in range(radius, image.shape[0] - radius):
        for x in range(radius, image.shape[1] - radius):

            pixel = 0
            for ii in range(y - radius, y + radius):
                for jj in range(x - radius, x + radius):
                    pixel += (image[ii][jj])

            new_img[y][x] = pixel // (num**2)
    return new_img

def removeBorder(img, border):
    
    newimg = np.empty( (img.shape[0]-border*2, img.shape[1]-border*2), np.uint8)
    for y in range(0, img.shape[0]-border*2):
        for x in range(0, img.shape[1]-border*2):
            newimg[y][x] = img[y+ border ][x+ border ]

    return newimg


def main():

    print ('Escolho o raio da mascara:'),
    n = input()*2 + 1
    border = n // 2

    img = cv2.imread('noise.png',0)
    img = cv2.copyMakeBorder(img, border,border,border,border, cv2.BORDER_CONSTANT, 0)



    img = media(img, n)

    # Removing the borders:
    new_img = removeBorder(img, border)


    cv2.imshow('Filtered image', new_img)
    cv2.waitKey(0)
    cv2.imwrite('media.png', new_img)

if __name__ == "__main__": main()
