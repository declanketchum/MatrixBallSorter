from PIL import Image
import numpy as np

img = Image.open("logo.png")
#take image uploaded on website
#img.show()

width = 20 #how many pixels wide
height = 20 #how many pixels tall
#maybe figure out how to keep the aspect ratio so that images are not stretched


img1 = img.resize((width,height)) #resize image to fit in matrix display
#print(img1.size)
#img1.show()

img2 = img1.convert("1") #convert image to black and white
#print(img2)
#img2.show()
#
pix = np.array(img2) #convert black and white image to an array of true and false which will map to black and white balls
#send bool array to ardino javascript


#print(pix)
