from typing import Optional

from fastapi import FastAPI
from fastapi.responses import FileResponse

file_path = "../website_files/website.html"
app = FastAPI()


@app.get("/")
def read_root():
    return FileResponse(file_path)


@app.get("/items/{item_id}")
def read_item(item_id: int, q: Optional[str] = None):
    return {"item_id": item_id, "q": q}
