# import maze as mz
from score import ScoreboardFake, Scoreboard
from BTinterface import BTinterface

import numpy as np
import pandas
import time
import sys
import os



def main():
    stage = 1
    # orders = ['f', 'r','r', 'l', 'r', 'r', 'f', 'f', 'h', 'h'] #h for halt
    orders = ['f', 'l', 'l', 'f', 'f', 'l', 'l', 'f', 'r',  'f'  ,'l', 'f', 'r', 'l', 'r', 'f', 'f', 'f', 'f', 'l', 'r', 'r', 'f', 'r', 'l', 'r', 'f', 'l', 'f', 'f', 'r', 'f', 'r', 'r', 'l', 'l', 'r', 'r', 'f', 'r', 'r', 'l', 'r', 'r', 'f', 'l', 'h', 'h']
    # orders = ['f','f','f','f','f','f','f','f','f','f','f']
    # maze = mz.Maze("python/data/small_maze.csv")
    # orders = ['f', 'r', 'f', 'f', 'f', 'f', 'f', 'l', 'l', 'r', 'l','l', 'h', 'h']
    interf = BTinterface()
    # # TODO : Initialize necessary variables
    interf.start()
    
    gameboard = Scoreboard("HOT_FIRE_XXX", "http://140.112.175.18:3000")
    # gameboard = ScoreboardFake("HOT_FIRE_XXX", "python/data/fakeUID.csv")
    
    
    while True:
        
        if interf.ser.waiting():
            tmp = interf.ser.SerialReadString()
            print(tmp)
            if (tmp == '$'): #on node
                stage += 1
                interf.ser.SerialWriteString(orders[stage])
                # print(orders[stage], end = '\n')
            elif tmp != "":
                gameboard.add_UID(tmp)
                print("current score :" + str(gameboard.getCurrentScore()))

    
    
    # if (sys.argv[1] == '0'):
    #     print("Mode 0: for treasure-hunting")
    #     # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible
        
    # elif (sys.argv[1] == '1'):
    #     print("Mode 1: Self-testing mode.")
    #     # TODO: You can write your code to test specific function.

if __name__ == '__main__':
    main()