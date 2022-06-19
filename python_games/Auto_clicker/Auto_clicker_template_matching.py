# -*- coding: utf-8 -*-
"""
Created on Fri Oct 22 15:56:54 2021

@author: LENOVO
"""

import cv2
import numpy as np
import pyautogui
import win32gui
import win32ui
import win32con

def nothing(x):
    pass

def screenshot():

    hwnd = None
    wDC = win32gui.GetWindowDC(hwnd)
    dcObj=win32ui.CreateDCFromHandle(wDC)
    cDC=dcObj.CreateCompatibleDC()
    dataBitMap = win32ui.CreateBitmap()
    dataBitMap.CreateCompatibleBitmap(dcObj, 1920, 1080)
    cDC.SelectObject(dataBitMap)
    cDC.BitBlt((0,0),(1920, 1080) , dcObj, (0,0), win32con.SRCCOPY)
    
    sIA = dataBitMap.GetBitmapBits(True)
    snip = np.fromstring(sIA, dtype = 'uint8')
    snip.shape = (1080,1920,4)
    snip = snip[25:1010, 700:1310]
    
    # Free Resources
    dcObj.DeleteDC()
    cDC.DeleteDC()
    win32gui.ReleaseDC(hwnd, wDC)
    win32gui.DeleteObject(dataBitMap.GetHandle())
    
    return snip

template = cv2.imread('snip.JPG', 0)
template_s = cv2.imread('s_start.JPG', 0)
template_d = cv2.imread('d_start.JPG', 0)

l_hue = 0
l_saturation = 156
l_value = 0
u_hue = 255
u_saturation = 255
u_value = 255
threshold = 0.9

l_blue = np.array([l_hue,l_saturation,l_value])
u_blue = np.array([u_hue,u_saturation,u_value])
start = False

while True:
    if cv2.waitKey(1) == ord('q'):
        cv2.destroyAllWindows()
        break
    
    frame = screenshot()
    # frame = np.array(frame)
    # frame = frame[25:1010, 700:1310]
    #frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    width_s, height_s = template_s.shape[::-1] 
    match_s = cv2.matchTemplate(frame_gray, template_s, cv2.TM_CCOEFF_NORMED)
    position_s = np.where(match_s >= threshold)
    
    if not start:
        for point in zip(*position_s[::-1]): 
            cv2.rectangle(frame, point, (point[0] + width_s, point[1] + height_s), (0, 255, 0), 5)
            pyautogui.click(point[0] + 700 + width_s/2, point[1] + 25 + height_s/2)
            start = True
            break
    
    width_d, height_d = template_d.shape[::-1] 
    match_d = cv2.matchTemplate(frame_gray, template_d, cv2.TM_CCOEFF_NORMED)
    position_d = np.where(match_d >= threshold) 
    
    if not start:
        for point in zip(*position_d[::-1]): 
            cv2.rectangle(frame, point, (point[0] + width_d, point[1] + height_d), (0, 255, 0), 5)
            pyautogui.click(point[0] + 700 + width_d/2, point[1] + 25 + height_d/2)
            start = True
            break

    mask = cv2.inRange(hsv, l_blue, u_blue)
    res_con = cv2.bitwise_and(frame, frame, mask= mask)
    res_gray = cv2.cvtColor(res_con, cv2.COLOR_RGB2GRAY)
    
    width, height = template.shape[::-1] 
    match = cv2.matchTemplate(res_gray, template, cv2.TM_CCOEFF_NORMED)
    position = np.where(match >= threshold) 
    
    if start:
        for point in zip(*position[::-1]): 
            cv2.rectangle(frame, point, (point[0] + width, point[1] + height), (0, 255, 0), 5)
            pyautogui.click(point[0]+700+width/2, point[1]+25+height/2)
            break
    
    
    cv2.imshow('Auto_cliker_Template_matching', frame)