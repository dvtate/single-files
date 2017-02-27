from tkinter import *;
from random import randint;
from time import sleep;

WIDTH = 500;
HEIGHT = 500;

# create the cells matrix
def init_cells(window, population):
	global HEIGHT;
	global WIDTH;
	
	cells = [[0 for x in range(WIDTH)] for y in range(HEIGHT)]; # declare matrix
	 
	
	# populate
	for cell in range(population):
		cells[randint(0, WIDTH - 1)][randint(0, HEIGHT - 1)] = True; 

	return cells

def update_cells(cells):
	ncells = cells;
	for x in range(WIDTH):
		for y in range(HEIGHT):
			neighbors_count = getNeighborCount(cells, (x, y));
			if cells[x][y] and (neighbors_count > 3 or neighbors_count < 2):
				ncells[x][y] = False;
			elif neighbors_count == 3:
				ncells[x][y] = True;

	
	return ncells;

def draw_cells(window, cells):
	for x in range(WIDTH):
		for y in range(HEIGHT):
			if (cells[x][y] == True):
				window.create_rectangle(x, y, x, y, fill = "black");
			else:
				window.create_rectangle(x, y, x, y, fill = "white", outline = "white");


def getNeighborCount(cells, coords):
	'''
	ret = [];
	if coords[0] - 1 > 0 and cells[coords[0] - 1][coords[1]]:
		ret.append([coords[0] - 1, coords[1]]);
	if coords[1] - 1 > 0 and cells[coords[0]][coords[1] - 1]:
		ret.append([coords[0], coords[1] - 1]);
	if coords[0] + 1 < WIDTH and cells[coords[0] - 1][coords[1]]:
		ret.append([coords[0] + 1, coords[1]]);
	if coords[1] + 1 < HEIGHT and cells[coords[0] - 1][coords[1]]:
		ret.append([coords[0], coords[1] + 1]);
	'''
	ret = 0;
	if coords[0] - 1 > 0 and cells[coords[0] - 1][coords[1]]:
		ret += 1;
	if coords[1] - 1 > 0 and cells[coords[0]][coords[1] - 1]:
		ret += 1;
	if coords[0] + 1 < WIDTH and cells[coords[0] - 1][coords[1]]:
		ret += 1;
	if coords[1] + 1 < HEIGHT and cells[coords[0] - 1][coords[1]]:
		ret += 1;
		
	return ret;
	

def main():
	global WIDTH;
	global HEIGHT;
	master = Tk();
	window = Canvas(master, width = WIDTH, height = HEIGHT, background = "white");
	window.grid();
	
	cells = init_cells(window, 500);
	
	#cells[4][4] = cells[4][5] = cells[5][4] = cells[5][5] = True;
	
	while True:
		draw_cells(window, cells);
		cells = update_cells(cells);
		window.update();
		sleep(0.5);
		

# emulating the functionality of C....
if __name__ == '__main__':
	main();
