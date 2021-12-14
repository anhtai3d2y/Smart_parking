import numpy as np
import cv2
import pytesseract
import matplotlib.pyplot as plt
from PIL import Image

img = cv2.imread('3.jpg')
cv2.imshow('Hinh anh goc',img)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
thresh = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY,11,2)
contours,h = cv2.findContours(thresh,1,2)
largest_rectangle = [0,0]
for cnt in contours:
  approx = cv2.approxPolyDP(cnt,0.01*cv2.arcLength(cnt,True),True)
  if len(approx)==4:
    area = cv2.contourArea(cnt)
    if area > largest_rectangle[0]:
      largest_rectangle = [cv2.contourArea(cnt),cnt,approx]
x,y,w,h = cv2.boundingRect(largest_rectangle[1])

image = img[y:y+h,x:x+w]
cv2.drawContours(img,[largest_rectangle[1]],0,(0,255,0),8)

cropped = img[y:y+h,x:x+w]
cv2.imshow('Danh dau doi tuong', img)

cv2.drawContours(img,[largest_rectangle[1]],0,(255,255,255),18)

#chuyen anh thanh file text
pytesseract.pytesseract.tesseract_cmd = 'C:\Program Files\Tesseract-OCR\\tesseract.exe'
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
blur = cv2.GaussianBlur(gray, (3,3), 0)
thresh = cv2.threshold(blur, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)[1]
cv2.imshow('CROP', thresh)
kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(3,3))
opening = cv2.morphologyEx(thresh,cv2.MORPH_OPEN, kernel, iterations=1)
invert = 255- opening
data = pytesseract.image_to_string(invert, lang='eng', config='--psm 6')
print("Thong tin nhan dien: ")
print(data)
cv2.waitKey()