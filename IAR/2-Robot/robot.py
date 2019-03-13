import pygame as pg
from random import randint
import numpy as np
##
from Settings import Settings
from Tile import Tile
##

def setup():
	# resolution = (1280, 720)
	resolution = (960, 720)

	pg.init()

	settings = Settings(resolution, 60)
	pg.display.set_caption('Mapa')

	screen  = pg.display.set_mode(resolution)

	settings.font = pg.font.Font(None, 30)
	settings.clock = pg.time.Clock()

	info_file = open("input/info2.in", "r")
	info = info_file.read().split()


	# == colors == #
	grass  = ( 10, 210,  90)
	water  = (  0, 120, 190)
	magma  = (227,  66,  52)
	purple = (105,  53, 156) #69359C
	purple2= (135,  93, 176) #875DB0
	purple3= (159, 125, 192) #9F7DC0
	# ============ #

	colors = [grass, water, magma, purple]

	wid = int(info[0])
	hei = int(info[1])

	mapa = np.zeros( (wid, hei), dtype = object)
	for y in range(0, hei):
		for x in range(0, wid):
			tipo = int(info[wid*y + x + 2])
			mapa[y, x] = Tile(colors[tipo])

			# mapa[y, x] = Tile( ( int(info[wid*y + 3*x + 2]), int(info[wid*y + 3*x + 3]), int(info[wid*y + 3*x + 4]) ) )

	return screen, settings, mapa

def chess(screen, settings):
	color = (180, 180, 255)
	black = (30,30,30)
	white = (220,220,220)

	w = settings.resolution[0]
	h = settings.resolution[1]

	num = 8
	thicc = 10
	cont = 0

	for y in range(0, num):
		for x in range(0, num):

			if(cont % 2 == 0):
				color = white
			else:
				color = black

			pg.draw.rect(screen, color,
							( ((w-h)/2) + (h * x) / num, 	# X Starting point
							(h * y) / num,	 				# Y Starting point
							(h / num),		 				# X size
							(h / num)))		 				# Y size
			cont += 1
		cont +=1

def drawMap(screen, settings, mapa):
	size = mapa.shape

	w = settings.resolution[0]
	h = settings.resolution[1]

	for i in range(0, size[0]):
		for j in range(0, size[1]):
			pg.draw.rect(screen, mapa[i, j].color,
							( ((w-h)/2) + (h * j) / size[0], 	# X Starting point
							(h * i) / size[1],	 				# Y Starting point
							(h / size[0]),		 				# X size
							(h / size[1]))) 					# Y size

			# pg.draw.rect(screen, pg.Color(0, 0, 0, 100),
			# 				( ((w-h)/2) + (h * j) / size[0],
			# 				(h * i) / size[1],
			# 				(h / size[0]),
			# 				(h / size[1])), 1)

def draw(screen, settings, mapa):
	background = (0, 0, 0)

	screen.fill(background)
	drawMap(screen, settings, mapa)
	# chess(screen, settings)
	update(screen, settings)


def update(screen, settings):
	pg.draw.rect(screen, pg.Color(0, 0, 0, 50), (5, 5, 75, 20))
	fps = settings.font.render("FPS: " + str(int(settings.clock.get_fps())), True, pg.Color('white'))
	screen.blit(fps, (5, 5))
	pg.display.flip()
	settings.clock.tick(settings.framerate)

def main():
	print("Starting...")

	screen, settings, mapa = setup()

	running = True
	while(running):
		draw(screen, settings, mapa)
		for event in pg.event.get():
			if event.type == pg.QUIT:
				running = False

if __name__ == "__main__": main()
