'''
Author: your name
Date: 2021-09-16 20:10:06
LastEditTime: 2021-09-19 17:52:39
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: \code\website\TransmitWeb.py
'''
import os

pathDir =  os.listdir("./")
for fileName in pathDir:
  if fileName.find(".html") == -1:
    continue

  File = open("./" + fileName,"r",encoding='utf-8')
  newFile = open("./" + fileName[0:-5] + ".cppStr","w",encoding='utf-8')
  while True:
    a = File.read(1)
    if a == "":
      break
    elif a == "\"":
      newFile.write("\\\"")
      continue
    elif a == "\n":
      continue
    newFile.write(a)
  File.close()
  newFile.close()