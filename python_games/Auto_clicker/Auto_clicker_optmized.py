# -*- coding: utf-8 -*-
"""
Created on Sun Oct 24 20:14:37 2021

@author: LENOVO

Press 's' to start clicking
First click: Get pixel color
2nd, 3rd, 4th and 5th clicks: For getting the tiles locations in four columns
Press 'q' to end the game
"""

import pyautogui
import time
import keyboard
import ctypes
import win32api

state_left = win32api.GetKeyState(0x01)
started = False
pos_1 = False
pos_2 = False
pos_3 = False
pos_4 = False
color = False
temp = False

def click_mouse(x,y):
    ctypes.windll.user32.SetCursorPos(x, y)
    ctypes.windll.user32.mouse_event(2, 0, 0, 0,0)
    time.sleep(0.02)
    ctypes.windll.user32.mouse_event(4, 0, 0, 0,0)
    
while True:
    if keyboard.is_pressed('s') == True: 
        temp = True
        break
    
while not started and temp:

    if win32api.GetKeyState(0x01) != state_left:  # Button state changed
        state_left = win32api.GetKeyState(0x01)
        
        if win32api.GetKeyState(0x01) < 0 and not color:    # Get pixel color
            x, y = pyautogui.position()
            rgb = pyautogui.screenshot().getpixel((x,y))
            time.sleep(0.5)
            color = True
            
        if win32api.GetKeyState(0x01) < 0 and not pos_1:    # Get position 1
            x1,y1 = pyautogui.position()
            time.sleep(0.5)
            pos_1 = True
            
        elif win32api.GetKeyState(0x01) < 0 and not pos_2:  # Get position 2
            x2,y2 = pyautogui.position()
            time.sleep(0.5)
            pos_2 = True
            
        elif win32api.GetKeyState(0x01) < 0 and not pos_3:  # Get position 3
            x3,y3 = pyautogui.position()
            time.sleep(0.5)
            pos_3 = True
            
        elif win32api.GetKeyState(0x01) < 0 and not pos_4:  # Get position 4
            x4,y4 = pyautogui.position()
            time.sleep(0.5)
            pos_4 = True
    
    if pos_1 and pos_2 and pos_3 and pos_4:
        started = True

while keyboard.is_pressed('q') == False and started:
    
    if pyautogui.pixel(x1, y1) == rgb:
        click_mouse(x1, y1)
        
    if pyautogui.pixel(x2, y2) == rgb:
        click_mouse(x2, y2)
        
    if pyautogui.pixel(x3, y3) == rgb:
        click_mouse(x3, y3)

    if pyautogui.pixel(x4, y4) == rgb:
        click_mouse(x4, y4)
