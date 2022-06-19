# -*- coding: utf-8 -*-
"""
Created on Tue Oct 19 14:00:47 2021

@author: LENOVO
"""

import pygame
import numpy as np
import random
import time
from enum import Enum

pygame.init()

class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    NONE = 3

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

font = pygame.font.SysFont('airal', 25)
font_init = pygame.font.SysFont('airal', 75)
font1 = pygame.font.SysFont('airal', 25)

car_main = pygame.image.load('car1.png')
car_obs_1 = pygame.image.load('car2.png')
car_obs_2 = pygame.image.load('car3.png')
car_obs_3 = pygame.image.load('car4.png')

car_main_rec = car_main.get_rect()
car_obs_rec_1 = car_obs_1.get_rect()
car_obs_rec_2 = car_obs_2.get_rect()
car_obs_rec_3 = car_obs_3.get_rect()

road = pygame.image.load('road.png')
car_height = 100
car_width = 50
offset = 2
step_size = 5

class CarGame:
    
    def __init__(self, w=640, h=640):
        self.h = h
        self.w = w
        
        # init display
        self.display = pygame.display.set_mode((self.w, self.h))
        pygame.display.set_caption('Snake')
        self.clock = pygame.time.Clock()
        
        # init game state
        car_main_rec.x = self.w/2 - car_width/2 + offset
        car_main_rec.y = self.h - car_height

        car_obs_rec_1.x, car_obs_rec_2.x, car_obs_rec_3.x = 217, 297, 372
        car_obs_rec_1.y, car_obs_rec_2.y, car_obs_rec_3.y = -100, -100, -100
        
        self.car_gamer = [car_main_rec.x, car_main_rec.y]
        self.car_obs_pos = [[car_obs_rec_1.x, car_obs_rec_1.y], [car_obs_rec_2.x, car_obs_rec_2.y], [car_obs_rec_3.x, car_obs_rec_3.y]]

        self.direction = Direction.NONE
        self.score = 0
        self.state = 1
        self.state_word = ['Left', 'Middle', 'Right']
        self.car_obs = [car_obs_1, car_obs_2, car_obs_3]
        self.x_pos = [217, 297, 372]
        self.game_started = False
        self._reset_states()
        
    def play_step(self):
        # user input
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                self.game_started = True
                if event.key == pygame.K_LEFT:
                    self.direction = Direction.LEFT
        
                elif event.key == pygame.K_RIGHT:
                    self.direction = Direction.RIGHT
        
        self._move(self.direction)
        self.car_position()
        
        # check if game over
        game_over = False
        if self._is_collision():
            game_over = True
            text = font_init.render("Game Over", True, WHITE)
            self.display.blit(text, [self.w/3.5,self.h/3.5])
            pygame.display.flip()
            time.sleep(3)
            return game_over, self.score 
        
        # Add new cars
        for i in range(0, 3):
            if self.car_obs_pos[i][1] > self.h:
                self.score += 1
                self.car_obs = random.sample(self.car_obs, len(self.car_obs))
                self._reset_states()
            
        # update ui and clock
        self._update_ui()
        self.clock.tick(min(self.score + step_size*5, 60))
        
        # return game over and score
        return game_over, self.score
    
    def car_position(self):
        if not self.game_started:                
            for i in self.car_list:
                self.car_obs_pos[i] = [self.x_pos[i], -100]
                        
        if self.game_started:
            for i in self.car_list:
                self._move_car(i, self.car_obs_pos[i])

    def _car_load(self, car, cord):
        self.display.blit(car, (cord[0], cord[1]))
    
    def _update_ui(self):
        self.display.fill(WHITE)
        self.display.blit(road, (0,0))
        
        if not self.game_started:
            text = font_init.render("Start Game", True, WHITE)
            self.display.blit(text, [self.w/3.5,self.h/3.5])
            text = font1.render("Avoid hitting other cars", True, WHITE)
            self.display.blit(text, [self.w/3,self.h/2.5])
        
        text = font1.render("Score: " + str(self.score), True, BLACK)
        self.display.blit(text, [10,10])
        text = font1.render("Lane: " + self.state_word[self.state], True, BLACK)
        self.display.blit(text, [10,30])
        self._car_load(car_main, self.car_gamer)
        self._car_load(self.car_obs[0], self.car_obs_pos[0])
        self._car_load(self.car_obs[1], self.car_obs_pos[1])
        self._car_load(self.car_obs[2], self.car_obs_pos[2])
        pygame.display.flip()
        
    def _move(self, direction):
        x = self.car_gamer[0]
        y = self.car_gamer[1]
        if direction == Direction.RIGHT and x < 368:
            x += step_size
            car_main_rec.x += step_size
            if x == 297:
                self.direction = Direction.NONE
                self.state = 1
            if x == 372:
                self.state = 2
        elif direction == Direction.LEFT and x >= 221:
            x -= step_size
            car_main_rec.x -= step_size
            if x == 297:
                self.direction = Direction.NONE
                self.state = 1
            if x == 217:
                self.state = 0
        elif direction == Direction.NONE:
            pass
        
        self.car_gamer = [x, y]
        
    def _move_car(self, num, position):
        y = position[1]
        y += step_size
        self.car_obs_pos[num] = [position[0], y]
        if num == 0:
            car_obs_rec_1.y += step_size
        
        if num == 1:
            car_obs_rec_2.y += step_size
            
        if num == 2:
            car_obs_rec_3.y += step_size
        
    def _reset_states(self):
        for i in range(0, 3):
            self.car_obs_pos[i] = [self.x_pos[i], -100]
        
        car_obs_rec_1.x, car_obs_rec_2.x, car_obs_rec_3.x = 217, 297, 372
        car_obs_rec_1.y, car_obs_rec_2.y, car_obs_rec_3.y = -100, -100, -100
        
        self.car_gamer = [car_main_rec.x, car_main_rec.y]
        self.car_obs_pos = [[car_obs_rec_1.x, car_obs_rec_1.y], [car_obs_rec_2.x, car_obs_rec_2.y], [car_obs_rec_3.x, car_obs_rec_3.y]]
        
        self.car_list = []
        for i in range(0, np.random.randint(2) + 1):
            self.car_list.append(np.random.randint(3))
            
    def _is_collision(self):
        if car_main_rec.colliderect(car_obs_rec_1) or car_main_rec.colliderect(car_obs_rec_2) or car_main_rec.colliderect(car_obs_rec_3):
            return True
            
        return False
        
if __name__ == '__main__':
    game = CarGame()
    
    # game loop 
    while True:
        game_over, score = game.play_step()
        
        if game_over:
            break      
    
    pygame.quit()