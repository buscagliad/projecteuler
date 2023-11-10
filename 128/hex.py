

import math
def is_prime(n):
	if n < 2: return False
	if n in [2, 3, 5, 7, 11, 13, 17, 19]: return True
	if n < 23: return False
	for i in range(2,int(math.sqrt(n))+1):
		if (n%i) == 0: return False
	return True

tilenumber = 0
upperLeftTile = None
centerTile = None
tileList = []
circleList = []

def getnum(t):
	if t == None: return -1
	return t.tile

class Tile:
	def __init__(self):
		global tilenumber
		global tileList
		tilenumber += 1
		self.tile = tilenumber
		self.north = None
		self.northwest = None
		self.southwest = None
		self.south = None
		self.southeast = None
		self.northeast = None
		self.black = False
		tileList.append(self)
		self.part2flip = False
		
	def display(self):
		print("      ", getnum(self.north))
		print(getnum(self.northwest), "      |     ",getnum(self.northeast))
		print("   \     |      /  ")
		print("      ", getnum(self))
		print("   /     |      \  ")
		print(getnum(self.southwest), "      |     ",getnum(self.southeast))
		print("      ", getnum(self.south))
		
	def flip(self, debug=False):
		if self.black:
			self.black = False
			if debug: print(self.tile, " flipping to White")
		else:
			self.black = True
			if debug: print(self.tile, " flipping to Black")


def findTile(tn):
	global tileList
	for t in tileList:
		if t.tile == n:
			return t

def checkNeighbors(tile):
	m = tile.tile
	d = [abs(tile.north.tile - m),
	     abs(tile.northeast.tile - m),
	     abs(tile.northwest.tile - m),
	     abs(tile.south.tile - m),
	     abs(tile.southwest.tile - m),
	     abs(tile.southeast.tile - m) ]
	np = 0
	for p in d:
		if is_prime(p): np += 1
	if np == 3:
		print("Tile: ", m, " diffs: ", d)
	return np
				

	
def createGrid(n):
	global upperLeftTile 
	global centerTile
	col = 1
	##
	## create first column:
	upperLeftTile = Tile()
	upperMostCurrentColTile = upperLeftTile
	tt = upperLeftTile
	for i in range(n-1):
		tt.south = Tile()
		tt.south.north = tt
		tt = tt.south

	while col <= n:
		tt = upperMostCurrentColTile
		#print(tt.tile)
		col += 1
		pt = None	# previous tile
		for i in range(n):
			nt = Tile()
			tt.northeast = nt
			if not tt.north is None:  tt.north.southwest = nt
			nt.southwest = tt
			nt.southeast = tt.north

			if pt is None:
				upperMostCurrentColTile = nt
			else:
				nt.north = pt
				pt.south = nt

			
			#
			# determine if center tile
			if col == n/2 and i == n/2:
				centerTile = nt
			
			#
			# update previous tile
			pt = nt
			tt = tt.south	# move down one row

			
def renumber(maxnum):
	global centerTile
	global circleList
	tilenumber = 1
	sequence = 0
	centerTile.tile = tilenumber
	tile = centerTile
	circleList.append(tile)
	done = False
	while tilenumber < maxnum:
		sequence += 1
		tile = tile.north
		endtile = tile
		tilenumber += 1
		print("Tile number changed from ", tile.tile, " to ", tilenumber)
		tile.tile = tilenumber
		circleList.append(tile)
		# (sw, s, se, ne, n, nw)
		for j in range(sequence):
			tile = tile.southwest
			tilenumber += 1
			tile.tile = tilenumber
			circleList.append(tile)
		for j in range(sequence):
			tile = tile.south
			tilenumber += 1
			if tile is None:
				print("present tile is ", endtile.tile)
			tile.tile = tilenumber
			circleList.append(tile)
		for j in range(sequence):
			tile = tile.southeast
			tilenumber += 1
			tile.tile = tilenumber
			circleList.append(tile)
		for j in range(sequence):
			tile = tile.northeast
			tilenumber += 1
			tile.tile = tilenumber
			circleList.append(tile)
		for j in range(sequence):
			tile = tile.north
			tilenumber += 1
			tile.tile = tilenumber
			circleList.append(tile)
		for j in range(sequence):
			tilenumber += 1
			tile = tile.northwest
			if  not endtile == tile:
				tile.tile = tilenumber
				circleList.append(tile)

	
	
createGrid(4)
centerTile.display()
centerTile.tile = 3023
renumber(4
)
centerTile.display()
circleList[0].display()
print ("cl size: ", len(circleList))
for t in circleList:
	c = checkNeighbors(t)
	if c == 3:
		print (t.tile, c)
