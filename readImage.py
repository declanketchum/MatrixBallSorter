from PIL import Image
import numpy as np

img = Image.open('olin_o.jpeg')

width = 20
height = 20

img1 = img.resize((width,height))
print(img1.size)

img2 = img1.convert("1")
img2.show()

pix = np.array(img2)
print(pix)
