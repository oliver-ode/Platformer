from opensimplex import OpenSimplex
from random import randint

"""
SETUP
"""
# Constants
WIDTH = 200
HEIGHT = 200
RESOLUTION = 7 #Larger value makes scale larger and more smooth
SEED = randint(1, 10000000)

# Variables
_map = []
ops = OpenSimplex(seed=SEED)

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

"""
MAIN
"""
fillBlank(_map)

for _y in range(HEIGHT):
    for _x in range(WIDTH):
        _map[_y][_x]=1 if ops.noise2d(x=_x/RESOLUTION, y=_y/RESOLUTION)>0 else 0

fileWrite()