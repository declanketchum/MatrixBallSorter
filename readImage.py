from PIL import Image
import numpy as np

img = Image.open("logo.png")
img.show()

width = 20
height = 20

img1 = img.resize((width,height))
print(img1.size)
img1.show()

img2 = img1.convert("1")
print(img2)
img2.show()
#
# pix = np.array(img2)
# print(pix)
