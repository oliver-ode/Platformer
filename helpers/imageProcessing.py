from PIL import Image

mapper = [[(  0,   0,   0,   0), 0],
          [(255,   0,   0, 255), 1],
          [(  0, 255,   0, 255), 2],
          [(  0,   0, 255, 255), 3]]

imageName = input("What is the name of the file: ")
imageExtension = input("What is the extension of the file: ")

image = Image.open(imageName+"."+imageExtension)
pixels = image.load()

def index2d(ref):
  for valMap in mapper:
    if ref in valMap:
      return(valMap[1])
  print("Value not added to mapper list. Please add this value: " + str(ref))
  return(-1)

width, height = image.size

f = open(imageName+".out", "w")

s = ""

for h in range(height):
  for w in range(width):
    s+=str(index2d(pixels[w,h]))+" "
  f.write(s[0:-1]+"\n") if h!=height-1 else f.write(s[0:-1])
  s=""

f.close()