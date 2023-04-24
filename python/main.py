import maze as mz
from score import ScoreboardFake, Scoreboard
from BTinterface import BTinterface

import numpy as np
import pandas
import time
import sys
import os


def hexTOstr(num):
    tmpStr = [0]*8
    numtmp = 0
    
    for i in range(7, -1, -1):
        if num % 16 < 10:
            tmpStr[i] = str(int(num%16))
        elif num % 16 == 10:
            tmpStr[i] = "A"
        elif num % 16 == 11:
            tmpStr[i] = "B"
        elif num % 16 == 12:
            tmpStr[i] = "C"
        elif num % 16 == 13:
            tmpStr[i] = "D"
        elif num % 16 == 14:
            tmpStr[i] = "E"
        elif num % 16 == 15:
            tmpStr[i] = "F"
        
        print(tmpStr[i])
            
        num -= num%16
        num /= 16

    return tmpStr[0] + tmpStr[1] + tmpStr[2] + tmpStr[3] + tmpStr[4] + tmpStr[5] + tmpStr[6] + tmpStr[7]

# print(hexTOstr(0x50335F7E))

def main():
    maze = mz.Maze("python/data/small_maze.csv")
    # gameboard = Scoreboard("HOT_FIRE_XXX", "http://140.112.175.18:3000")
    gameboard = ScoreboardFake("HOT_FIRE_XXX", "python/data/fakeUID.csv")
    interf = BTinterface()
    # # TODO : Initialize necessary variables
    interf.start()
    
    while True:
        if interf.get_UID():
            gameboard.add_UID(hexTOstr(interf.get_UID()))

    
    
    # if (sys.argv[1] == '0'):
    #     print("Mode 0: for treasure-hunting")
    #     # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible
        
    # elif (sys.argv[1] == '1'):
    #     print("Mode 1: Self-testing mode.")
    #     # TODO: You can write your code to test specific function.

if __name__ == '__main__':
    main()