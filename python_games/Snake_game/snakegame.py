# -*- coding: utf-8 -*-
"""
Created on Tue Oct  5 13:14:23 2021

@author: LENOVO
"""

import pygame
import random
import time
from enum import Enum
from collections import namedtuple

pygame.init()

font = pygame.font.SysFont('airal', 25)
font_init = pygame.font.SysFont('airal', 75)
font1 = pygame.font.SysFont('airal', 25)
class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    UP = 3
    DOWN = 4
    NONE = 5
    

Point = namedtuple('Point', 'x, y')

BLOCK_SIZE = 20
SPEED = 5
WHITE = (255, 255, 255)
GREEN = (0, 200, 0)
BLUE1 = (0, 0, 255)
BLUE2 = (0, 100, 255)
BLACK = (0, 0, 0)
RED = (200, 0, 0)

class SnakeGame:
    
    def __init__(self, w=640, h=480):
        self.h = h
        self.w = w
        # init display
        self.display = pygame.display.set_mode((self.w, self.h))
        pygame.display.set_caption('Snake')
        self.clock = pygame.time.Clock()
        
        # init game state
        self.direction = Direction.NONE
        
        self.head = Point(self.w/2, self.h/2)
        self.snake = [self.head,
                      Point(self.head.x-BLOCK_SIZE, self.head.y),
                      Point(self.head.x-(2*BLOCK_SIZE), self.head.y)]
        
        self.score = 0
        self.food = None
        self.block = None
        self._place_food()
        self._place_block()

        
    def _place_food(self):
        x = random.randint(0, (self.w-BLOCK_SIZE)//BLOCK_SIZE)*BLOCK_SIZE
        y = random.randint(0, (self.h-BLOCK_SIZE)//BLOCK_SIZE)*BLOCK_SIZE
        self.food = Point(x, y)
        
        if self.food in self.snake:
            self._place_food()
    
    def _place_block(self):
        x = random.randint(0, (self.w-BLOCK_SIZE)//BLOCK_SIZE)*BLOCK_SIZE
        y = random.randint(0, (self.h-BLOCK_SIZE)//BLOCK_SIZE)*BLOCK_SIZE
        self.block = Point(x, y)
        if (self.food.x == self.block.x and self.food.y == self.block.y) or (self.block in self.snake):
            self._place_block()
        
    def play_step(self):
        # collect user input
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT and self.direction != Direction.RIGHT and self.direction != Direction.LEFT:
                    self.direction = Direction.LEFT
        
                elif event.key == pygame.K_RIGHT and self.direction != Direction.LEFT and self.direction != Direction.RIGHT:
                    self.direction = Direction.RIGHT

                elif event.key == pygame.K_UP and self.direction != Direction.DOWN and self.direction != Direction.UP:
                    self.direction = Direction.UP
                        
                elif event.key == pygame.K_DOWN and self.direction != Direction.UP and self.direction != Direction.DOWN:
                    self.direction = Direction.DOWN
                           
        # move
        self._move(self.direction)
        self.snake.insert(0, self.head)
        
        # check if game over
        game_over = False
        if self._is_collision():
            game_over = True
            return game_over, self.score
        
        # place new food and block or just move
        if self.head == self.food:
            self.score += 1
            self._place_food()
            self._place_block()
        
        else:
            self.snake.pop()
            
        if self.food == self.block:
            self._place_block()
            self._place_food()
        
            
        #  game over if hit the block
        if self.block == self.snake[0]:
            text = font_init.render("Game Over", True, WHITE)
            self.display.blit(text, [self.w/3.5,self.h/3.5])
            pygame.display.flip()
            time.sleep(3)
            game_over = True
            return game_over, self.score
            
        # update ui and clock
        self._update_ui()
        self.clock.tick(min(SPEED + self.score, 25))
        
        # return game over and score
        return game_over, self.score
    
    def _is_collision(self):
        # hits boundary
        if self.direction == Direction.NONE:
            return False
        if self.head.x > self.w - BLOCK_SIZE:
            self.head = Point(0 - BLOCK_SIZE, self.head.y)
            return False
        if self.head.x < 0:
            self.head = Point(self.w, self.head.y)
            return False
        if self.head.y > self.h - BLOCK_SIZE:
            self.head = Point(self.head.x, 0 - BLOCK_SIZE)
            return False
        if self.head.y < 0:
            self.head = Point(self.head.x, self.h)
            return False
        
        # hits itself
        if self.head in self.snake[1:]:
            text = font_init.render("Game Over", True, WHITE)
            self.display.blit(text, [self.w/3.5,self.h/3.5])
            pygame.display.flip()
            time.sleep(3)
            return True
        
        return False
    
    def _update_ui(self):
        self.display.fill(BLACK)
        
        for pt in self.snake:
            pygame.draw.rect(self.display, BLUE1, pygame.Rect(pt.x, pt.y, BLOCK_SIZE, BLOCK_SIZE))
            pygame.draw.rect(self.display, BLUE2, pygame.Rect(pt.x+4, pt.y+4, 12, 12))
            
        pygame.draw.rect(self.display, GREEN, pygame.Rect(self.food.x, self.food.y, BLOCK_SIZE, BLOCK_SIZE))
        
        pygame.draw.rect(self.display, RED, pygame.Rect(self.block.x, self.block.y, BLOCK_SIZE, BLOCK_SIZE))
        
        text = font.render("Score: " + str(self.score), True, WHITE)
        self.display.blit(text, [0,0])
        
        if self.direction == Direction.NONE:
            text = font_init.render("Start Game", True, WHITE)
            self.display.blit(text, [self.w/3.5,self.h/3.5])
            text = font1.render("Eat the green fruit to score", True, WHITE)
            self.display.blit(text, [self.w/3,self.h/2.5])
            text = font1.render("Avoid hitting the red block", True, WHITE)
            self.display.blit(text, [self.w/3,self.h/2.25])
        pygame.display.flip()
        
    def _move(self, direction):
        x = self.head.x
        y = self.head.y
        if direction == Direction.RIGHT:
            x += BLOCK_SIZE
        elif direction == Direction.LEFT:
            x -= BLOCK_SIZE
        elif direction == Direction.DOWN:
            y += BLOCK_SIZE
        elif direction == Direction.UP:
            y -= BLOCK_SIZE
        elif direction == Direction.NONE:
            pass
            
        self.head = Point(x, y)

if __name__ == '__main__':
    game = SnakeGame()
    
    # game loop 
    while True:
        game_over, score = game.play_step()
        
        if game_over == True:
            break
    print('Final Score: '+ str(score))       
    
    pygame.quit()