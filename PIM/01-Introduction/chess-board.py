import numpy as np
import cv2

def makeBoard(x, y, sqr_size):

	board = np.zeros( (256, 256), np.uint8)

	ii = jj = 0

	for i in range(0, board.shape[0], sqr_size):
		ii += 1
		for j in range(0, board.shape[1], sqr_size):
			jj += 1
			for k in range(i, i + sqr_size):
				for l in range(j, j + sqr_size):
					board[k][l] = ( (ii+jj) %2) * 255

	return board


board = makeBoard(256,256,32)

cv2.imshow('Image', board)
cv2.waitKey(0)
cv2.destroyAllWindows()