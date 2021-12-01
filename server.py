from typing import Optional

from fastapi import FastAPI
from fastapi.responses import FileResponse

file_path = "/website.html"
app = FastAPI()


@app.get("/")
def read_root():
    return FileResponse(file_path)

@app.post("/upload")
async def create_upload_file(file: UploadFile = File(...)):
    return {"filename": file.filename}
    #confirm image is compatible
    #resize image and convert to black and white and create array
    #save array
    #return the new image and image id

@app.post("/confirm")
    #confirm image id
    #send array to ardino
    #return printing message


@app.get("/items/{item_id}")
def read_item(item_id: int, q: Optional[str] = None):
    return {"item_id": item_id, "q": q}
