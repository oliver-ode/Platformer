import random

"""
SETUP
"""
# Constants
WIDTH = 200
HEIGHT = 200
SEED = None #If you want a random put "None"
FILLPERCENT = 50
SURROUND = 1
GROW = 4
SMOOTHING = 10

# Variables
_map = []

# Initialization
random.seed(SEED, 2)

"""
FUNCTIONS
"""
def fillBlank(mapp):
    mapp.clear()
    for y in range(HEIGHT):
        mapp.append([-1]*WIDTH)

def printMap():
    for y in range(HEIGHT):
        print(_map[y])

def fileWrite():
    f = open("out.map", "w")
    s=""
    for y in range(HEIGHT):
        for x in range(WIDTH):
            s+=str(_map[y][x])+" "
        f.write(s[0:-1]+"\n") if y!=HEIGHT-1 else f.write(s[0:-1])
        s=""
    f.close()


def surroundingWallCount(gridX, gridY):
    cnt = 0
    for row in range(gridY-SURROUND, gridY+SURROUND+1):
        for col in range(gridX-SURROUND, gridX+SURROUND+1):
            if row!=0 and row<HEIGHT and col!=0 and col<WIDTH:
                if row!=gridY or col!=gridX:
                    cnt+=_map[row][col]
            else:
                cnt+=1
    return cnt

"""
MAIN
"""
fillBlank(_map)

for y in range(HEIGHT):
    for x in range(WIDTH):
        _map[y][x] = 0 if random.randint(1, 100) > FILLPERCENT else 1

for y in range(HEIGHT):
    for x in range(WIDTH):
        if y==0 or x==0 or y==HEIGHT-1 or x==WIDTH-1:
            _map[y][x] = 1

for i in range(SMOOTHING):
    newMap=[]
    fillBlank(newMap)
    for y in range(HEIGHT):
        for x in range(WIDTH):
            neighbourWallTiles = surroundingWallCount(x, y)
            if neighbourWallTiles>GROW:
                newMap[y][x]=1
            elif neighbourWallTiles<GROW:
                newMap[y][x]=0
            else:
                newMap[y][x]=_map[y][x]
    _map=newMap

fileWrite()