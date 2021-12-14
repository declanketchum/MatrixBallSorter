from PIL import Image
import numpy as np
import io
import serial
import time


img = Image.open("bird.jpg")
#img.show()
width = 35 #how many pixels wide
height = 35 #how many pixels tall
area = width*height
#maybe figure out how to keep the aspect ratio so that images are not stretched
resizedImg = img.resize((width,height)) #resize image to fit in matrix display
printImg = resizedImg.convert("1") #convert image to black and white
#printImg.show()
#send img2 back to to website
byteio = io.BytesIO()
printImg.save(byteio, format = "jpeg")
imgByteArr = byteio.getvalue()

pix = np.array(printImg)
#print(pix)
pix1arr = np.reshape(pix, area, order= "F")
print(pix1arr)
pixStr = ""
for p in pix1arr:
    pixStr = pixStr + str(int(p))
pixStr = pixStr + '\n'
print(pixStr)
#pixBytes = pixStr.encode('utf-8')

#data = pix1arr.tobytes()
data = pixStr + str(height) + '\n' + str(width) + '\n'
dataB = data.encode('utf-8')
print(data)

#
# a = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])
# print(a)
# b = np.reshape(a, 8, order= "F")
# print(b)

baud = 115200

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', baud, timeout=1)
    ser.reset_input_buffer()

#while True:
    ser.write(dataB)
    print("sending data")
    #line = ser.readline().decode('utf-8').rstrip()
    #print(line)
    time.sleep(1)
