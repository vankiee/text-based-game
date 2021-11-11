# COMP2113-Text-based-game

Members: Liew Van Kie, Au Cheuk Ying 

Game description & Basic game rules

NOTE: Please do not run the game on Mac Terminal. The game will work fine, but certain features will not be displayed.

Single-player, mystery and reasoning game which the player has to escape from all the rooms to win. 
Game starts with a randomized room. There will be 3 rooms in total. In each room, there will be 2 riddles to be found in 2 out of the 4 areas. The player needs to correctly choose the areas that contain the riddles, and then pick the right answer to the riddle from 3 choices. The player can only proceed to the next room once they have solved the two riddles successfully.
The player wins when they successfully escape all 3 rooms.

## Game demo

https://user-images.githubusercontent.com/44122417/141270484-4859c767-cdf8-44ac-b8bd-e1bb72f374ef.mp4

## Compilation and execution instructions

Type:
1. make clean
2. make all
3. ./game_loop

## Features/functions implemented

1. srand() and rand(): To generate a random room number to be the starting room for the player, and generate random comments after player's responses.
2. In game_loop.cpp, we used vectors to store random comments. We used vectors to store areas in each room. In rooms.h, we used struct to construct rooms. In areas.h, we used struct to construct areas.
3. Rooms are stored in dynamic arrays. After the player has unlocked the next room, the previous room will be deleted from the rooms vector. After all rooms have been solved, the rooms vector is deleted from the dynamic array.
4. Metadata files contain room name and their 4 areas. Riddles files contain riddles, the correct answer to the riddles and the multiple answer choices. 
5. game_loop.cpp, rooms.h, areas.h



