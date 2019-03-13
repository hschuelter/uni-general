import cv2
import math
import imutils
import datetime
import numpy as np
from skimage import feature
from skimage import exposure

def findOcurrence(imageHog, templateHog):
    startV = 0
    endV = imageHog.shape[0] - templateHog.shape[0]
    startH = 0
    endH = imageHog.shape[1] - templateHog.shape[1]
    for i in range(startV, endV):
        for j in range(startH, endH):
            current = imageHog[i:i+templateHog.shape[1], j:j+templateHog.shape[0]]
            if current == templateHog:
                return current

    return None

def generateHOG(imgName):
    roughImage = cv2.imread(imgName, 0)
    image = cv2.resize(roughImage,(roughImage.shape[1]//4, roughImage.shape[0]//4), interpolation = cv2.INTER_CUBIC)

    (H, imageHOG) = feature.hog(image, orientations=9, pixels_per_cell=(8, 8),
    cells_per_block=(2, 2), transform_sqrt=True, block_norm="L2-Hys",
    visualise=True)
    imageHOG = exposure.rescale_intensity(imageHOG, out_range=(0, 255))
    imageHOG = imageHOG.astype("uint8")

    return imageHOG, image


def main():
    # imageHOG, image = generateHOG('boruto.jpg')
    start = datetime.datetime.now()
    hoggeru = cv2.HOGDescriptor()
    image = cv2.imread('bus.jpeg')
    image = imutils.resize(image, width=min(400, image.shape[1]))

    hog = cv2.HOGDescriptor()
    hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

    (rects, weights) = hog.detectMultiScale(image, winStride=(8,8),
	padding=(16,16), scale=1.02 , useMeanshiftGrouping=False)
    print("[INFO] detection took: {}s".format(
	(datetime.datetime.now() - start).total_seconds()))

    print (rects)

    # draw the original bounding boxes
    for (x, y, w, h) in rects:
    	cv2.rectangle(image, (x, y), (x + w, y + h), (255, 0, 255), 2)

    cv2.imshow("Detections", image)
    cv2.waitKey(0)
    # print(hoggeru.getDescriptorSize())
    # #templateHOG = generateHOG('butiful.png')
    # #findu = findOcurrence(imageHOG, templateHOG)
    # #print(findu==None)
    #
    # #normalize
    # image = np.sqrt(image).astype("uint8")
    #
    # cv2.imwrite('norm-bolt.png', image)
    # #cv2.imwrite('bolt.png', rough)
    # #cv2.imshow('Template', templateHOG)
    cv2.destroyAllWindows()




main()
