import cv2 as cv
import numpy as np

def separate_color(frame):
    cv.imshow("原图", frame)
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)                              #色彩空间转换为hsv，便于分离
    lower_hsv = np.array([165,43,46])                                      #提取颜色的低值
    high_hsv = np.array([180,255,255])                                     #提取颜色的高值
    mask = cv.inRange(hsv, lowerb = lower_hsv, upperb = high_hsv)           #下面详细介绍
    cv.imshow("first", mask)
    #get result
    res = cv.bitwise_and(frame, frame, mask= mask)
    #cv.imshow("inRange", mask)
    cv.imshow("TESXT", frame)
    
image = "./test.png"
src = cv.imread(image)
separate_color(src)
cv.waitKey(0)