from PIL import Image
import numpy as np

mapper = [[(255, 255, 255, 255), 0], 
          [(  0,   0,   0, 255), 1],
          [(  0, 255,   0, 255), 2], 
          [(  0,   0, 255, 255), 3]]

mapName = input("What is the name of the map: ")

f = open(mapName+".map", "r")
_map = f.read().split("\n")
f.close()

def index2d(ref):
    for valMap in mapper:
        if int(ref) in valMap:
            return valMap[0]
    print("Value not added to mapper list. Please add this value: " + str(ref))
    return -1

def printMap():
    for y in range(len(_map)):
        print(_map[y])

for i in range(len(_map)):
    _map[i] = _map[i].split()

for y in range(len(_map)):
    for x in range(len(_map[0])):
        _map[y][x]=index2d(_map[y][x])

array = np.array(_map, dtype=np.uint8)

image = Image.fromarray(array)
image.save(mapName+".png")