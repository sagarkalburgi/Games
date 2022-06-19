
import pygame
import numpy as np
import random
import time
from enum import Enum

pygame.init()


class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    DOWN = 3
    UP = 4
    NONE = 5


WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

font = pygame.font.SysFont('airal', 25)
font_init = pygame.font.SysFont('airal', 75)
font1 = pygame.font.SysFont('airal', 25)

step_size = 2
spaceship_width = 54
spaceship_height = 66
factor = 0.25
alienship_size = 75


class AlienShooting(pygame.sprite.Sprite):

    def __init__(self, w=640, h=640):
        self.h = h
        self.w = w

        # init display
        self.display = pygame.display.set_mode((self.w, self.h))
        pygame.display.set_caption('AlienShooting')
        self.clock = pygame.time.Clock()

        # init game state
        self.spaceship_main = pygame.sprite.Sprite()
        self.spaceship_main.image = pygame.image.load('spacecraft_1.png').convert_alpha()

        self.spaceship_laser = pygame.sprite.Sprite()
        self.spaceship_laser.image = pygame.image.load('laser_spacecraft.png').convert_alpha()
        self.spaceship_laser.rect = self.spaceship_laser.image.get_rect()
        self.shooting = False
        self.laser_available = True

        self.alien_laser = pygame.sprite.Sprite()
        self.alien_laser.image = pygame.image.load('laser_alien.png').convert_alpha()
        self.alien_laser.rect = self.alien_laser.image.get_rect()
        self.alien_shooting = False
        self.alien_falling = False
        self.trigger = False
        self.idx = 0

        self.alien_spacecraft1 = pygame.sprite.Sprite()
        self.alien_spacecraft1.image = pygame.image.load('spacecraft_alien.png').convert_alpha()
        self.alien_spacecraft2 = pygame.sprite.Sprite()
        self.alien_spacecraft2.image = pygame.image.load('spacecraft_alien.png').convert_alpha()
        self.alien_spacecraft3 = pygame.sprite.Sprite()
        self.alien_spacecraft3.image = pygame.image.load('spacecraft_alien.png').convert_alpha()
        self.alien_spacecraft4 = pygame.sprite.Sprite()
        self.alien_spacecraft4.image = pygame.image.load('spacecraft_alien.png').convert_alpha()
        self.alien_spacecraft5 = pygame.sprite.Sprite()
        self.alien_spacecraft5.image = pygame.image.load('spacecraft_alien.png').convert_alpha()
        self.alien_spacecraft_active = [True, True, True, True, True]
        self.move = True

        self.spaceship_main.rect = self.spaceship_main.image.get_rect()
        self.spaceship_main.rect.x = self.w / 2 - spaceship_width / 2
        self.spaceship_main.rect.y = self.h * 0.75

        self.spacecrafts = [self.alien_spacecraft1, self.alien_spacecraft2, self.alien_spacecraft3,
                            self.alien_spacecraft4, self.alien_spacecraft5]

        for alien in self.spacecrafts:
            alien.rect = alien.image.get_rect()

        self.alien_direction_right = []
        for i in range(len(self.spacecrafts)):
            self.alien_direction_right.append(random.choice([True, False]))

        self.game_started = False
        self.initialization = False
        self.direction = Direction.NONE
        self.time = time.time()

        self.score = 0

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

                if event.key == pygame.K_RIGHT:
                    self.direction = Direction.RIGHT

                if event.key == pygame.K_UP:
                    self.direction = Direction.UP

                if event.key == pygame.K_DOWN:
                    self.direction = Direction.DOWN

                if event.key == pygame.K_SPACE:
                    self.direction = Direction.NONE

                if event.key == pygame.K_q:
                    self.shooting = True

                if event.key == pygame.K_ESCAPE:
                    return self.score, True

            if event.type == pygame.KEYUP:
                self.direction = Direction.NONE

        # Move the spaceship
        self._move(self.direction)

        # check if game over
        if self._is_collision:
            gameover_text = font_init.render("Game Over", True, WHITE)
            score_text = font_init.render(f"Score: {self.score}", True, WHITE)
            self.display.blit(gameover_text, [self.w / 3.5, self.h / 3.5])
            self.display.blit(score_text, [self.w / 3, self.h / 2.5])
            pygame.display.flip()
            time.sleep(3)
            return True, self.score

        # Add new alien spaceships

        # Randomly move alien spaceships
        self._alien_init()
        self._check_directions()
        self.initialization = True

        if abs(self.time - time.time()) >= 3:
            if not self.move:
                self.move = True
            else:
                self.move = False
            self.time = time.time()

        if self.move:
            self._move_aliens()

        self._check_fall()
        self._alien_fall()
        self._alien_shoot()
        self._shoot()
        self._move_laser()
        self._destroy_alien()
        # update ui and clock
        self._update_ui()
        self.clock.tick(min(self.score + step_size * 75, 150))
        # return game over and score
        return False

    def _update_ui(self):
        self.display.fill(BLACK)

        self.display.blit(self.spaceship_main.image, (self.spaceship_main.rect.x, self.spaceship_main.rect.y))

        if self.shooting:
            self.display.blit(self.spaceship_laser.image, (self.spaceship_laser.rect.x, self.spaceship_laser.rect.y))

        if self.alien_shooting:
            self.display.blit(self.alien_laser.image, (self.alien_laser.rect.x, self.alien_laser.rect.y))

        for idx, alien in enumerate(self.spacecrafts):
            if self.alien_spacecraft_active[idx]:
                self.display.blit(alien.image, (alien.rect.x, alien.rect.y))

        if not self.game_started:
            text = font_init.render("Start Game", True, WHITE)
            self.display.blit(text, [self.w / 3.5, self.h / 3.5])
            text = font1.render("Shoot the Alien Spaceships", True, WHITE)
            self.display.blit(text, [self.w / 2.5, self.h / 2.5])

        text = font1.render("Score: " + str(self.score), True, WHITE)
        self.display.blit(text, [10, 10])

        pygame.display.flip()

    def _move(self, direction):
        if direction == Direction.RIGHT and self.spaceship_main.rect.x < self.w - spaceship_width:
            self.spaceship_main.rect.x += step_size
        elif direction == Direction.LEFT and self.spaceship_main.rect.x > 0:
            self.spaceship_main.rect.x -= step_size
        elif direction == Direction.DOWN and self.spaceship_main.rect.y < self.h - spaceship_height:
            self.spaceship_main.rect.y += step_size
        elif direction == Direction.UP and self.spaceship_main.rect.y > 0:
            self.spaceship_main.rect.y -= step_size
        elif direction == Direction.NONE:
            pass

    def _check_directions(self):

        for idx, dir in enumerate(self.alien_direction_right):
            if self.alien_spacecraft_active[idx] and self.spacecrafts[idx].rect.x >= self.w - alienship_size:
                self.alien_direction_right[idx] = False
                self.spacecrafts[idx].rect.y += int(5 + self.score * factor)

            if self.alien_spacecraft_active[idx] and self.spacecrafts[idx].rect.x < 0:
                self.alien_direction_right[idx] = True
                self.spacecrafts[idx].rect.y += int(5 + self.score * factor)

    def _move_aliens(self):
        if not self.game_started:
            return

        for idx, dir in enumerate(self.alien_direction_right):
            if dir:
                self.spacecrafts[idx].rect.x += 1
            else:
                self.spacecrafts[idx].rect.x -= 1


    def _check_fall(self):
        if self.score % 10 != 0 and not self.alien_falling and self.score > 0:
            self.alien_falling = True
            self.idx = np.random.randint(len(self.spacecrafts))

    def _alien_fall(self):
        if self.score % 10 == 0 and self.alien_falling and self.score > 0:
            self.trigger = True

        if self.trigger:
            self.spacecrafts[self.idx].rect.y += 1
            if self.spacecrafts[self.idx].rect.y >= self.h:
                self._alien_reappear(self.idx)
                self.alien_falling = False
                self.trigger = False


    def _alien_shoot(self):
        if not self.game_started:
            return

        if np.random.randint(1000) < 2*self.score*factor and not self.alien_shooting:
            idx = np.random.randint(len(self.spacecrafts))
            self.alien_laser.rect.x = self.spacecrafts[idx].rect.x + 15
            self.alien_laser.rect.y = self.spacecrafts[idx].rect.y + 40
            self.alien_shooting = True

    @property
    def _is_collision(self):
        if not self.game_started:
            return False

        for idx in range(len(self.spacecrafts)):
            if self.alien_spacecraft_active[idx] and pygame.sprite.collide_mask(self.spaceship_main, self.spacecrafts[idx]):
                return True

        if pygame.sprite.collide_mask(self.spaceship_main, self.alien_laser):
            return True

        return False

    def _alien_init(self):
        for idx in range(len(self.spacecrafts)):
            if self.alien_spacecraft_active[idx] and not self.game_started and not self.initialization:
                self._random_location(self.spacecrafts[idx].rect)
                while self._alien_collide_check(self.spacecrafts[idx], idx):
                    self._random_location(self.spacecrafts[idx].rect)

            if not self.alien_spacecraft_active[idx] and self.game_started and self.initialization:
                self._random_location(self.spacecrafts[idx].rect)
                while self._alien_collide_check(self.spacecrafts[idx], idx):
                    self._random_location(self.spacecrafts[idx].rect)
                self.alien_spacecraft_active[idx] = True

    def _random_location(self, rect):
        rect.x = np.random.randint(alienship_size, self.w - alienship_size)
        rect.y = np.random.randint(alienship_size, self.h/2 - 100)

    def _alien_reappear(self, idx):
        if self.alien_falling and self.spacecrafts[idx].rect.y >= self.h:
            self._random_location(self.spacecrafts[idx].rect)
            for i in range(len(self.spacecrafts)):
                if i == idx:
                    continue
                if self.spacecrafts[i].rect.colliderect(self.spacecrafts[idx].rect):
                    self._random_location(self.spacecrafts[idx].rect)

    def _alien_collide_check(self, spacecraft, idx):
        for i in range(len(self.spacecrafts)):
            if i == idx:
                continue
            if self.alien_spacecraft_active[i] and spacecraft.rect.colliderect(self.spacecrafts[i].rect):
                return True

        return False

    def _shoot(self):
        if self.shooting and self.laser_available:
            self.spaceship_laser.rect.x = self.spaceship_main.rect.x + 15
            self.spaceship_laser.rect.y = self.spaceship_main.rect.y - 40
            self.laser_available = False

    def _move_laser(self):
        if self.shooting:
            self.spaceship_laser.rect.y -= 5
            if self.spaceship_laser.rect.y <= -50:
                self.shooting = False
                self.laser_available = True

        if self.alien_shooting:
            self.alien_laser.rect.y += 5
            if self.alien_laser.rect.y > self.h:
                self.alien_shooting = False

    def _destroy_alien(self):
        for idx in range(len(self.spacecrafts)):
            if idx == self.idx:
                continue
            if self.alien_spacecraft_active[idx] and pygame.sprite.collide_mask(self.spaceship_laser, self.spacecrafts[idx]):
                self.alien_spacecraft_active[idx] = False
                self.spacecrafts[idx].rect.x = 1000
                self.spacecrafts[idx].rect.y = 1000
                self.spaceship_laser.rect.x = -1000
                self.spaceship_laser.rect.y = -1000
                self.laser_available = True
                self.shooting = False
                self.score += 1
                return

        if pygame.sprite.collide_mask(self.spaceship_laser, self.spacecrafts[self.idx]):
            self.alien_spacecraft_active[self.idx] = False
            self.spacecrafts[self.idx].rect.x = 1000
            self.spacecrafts[self.idx].rect.y = 1000
            self.spaceship_laser.rect.x = -1000
            self.spaceship_laser.rect.y = -1000
            self.laser_available = True
            self.trigger = False
            self.alien_falling = False
            self.shooting = False
            self.score += 1
            return

        if pygame.sprite.collide_mask(self.spaceship_laser, self.alien_laser):
            self.spaceship_laser.rect.x = -1000
            self.spaceship_laser.rect.y = -1000
            self.alien_laser.rect.x = -2000
            self.alien_laser.rect.y = -2000
            self.laser_available = True
            self.alien_shooting = True
            self.shooting = False
            return


if __name__ == '__main__':
    game = AlienShooting()

    # game loop 
    while True:
        game_over = game.play_step()

        if game_over:
            break

    pygame.quit()
