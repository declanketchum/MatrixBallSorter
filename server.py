from typing import Optional

from fastapi import FastAPI, File, UploadFile, Response
from fastapi.responses import FileResponse
from PIL import Image
import numpy as np
import io
import serial

file_path = "website.html"
app = FastAPI()


@app.get("/")
def read_root():
    return FileResponse(file_path)

@app.post("/upload")
async def create_upload_file(uploadFile: UploadFile = File(...)):
    img = Image.open(uploadFile.file)
    width = 35 #how many pixels wide
    height = 35 #how many pixels tall
    #maybe figure out how to keep the aspect ratio so that images are not stretched
    resizedImg = img.resize((width,height)) #resize image to fit in matrix display
    printImg = resizedImg.convert("1") #convert image to black and white
    #send img2 back to to website
    byteio = io.BytesIO()
    printImg.save(byteio, format = "jpeg")
    imgByteArr = byteio.getvalue()

    pix = np.array(printImg) #convert black and white image to an array of true and false which will map to black and white balls
    #send bool array to ardino javascript
    return Response(content=imgByteArr, media_type="image/jpeg")
    #confirm image is compatible
    #resize image and convert to black and white and create array
    #save array
    #return the new image and image id

#@app.post("/confirm")
    #confirm image id
    #send array to ardino
    #return printing message

#
# @app.get("/items/{item_id}")
# def read_item(item_id: int, q: Optional[str] = None):
#     return {"item_id": item_id, "q": q}
