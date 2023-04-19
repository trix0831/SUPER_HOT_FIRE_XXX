from node import *
import numpy as np
import csv
import pandas
import queue
from enum import IntEnum
import math


class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5


class Maze:
    def __init__(self, filepath):
        # TODO : read file and implement a data structure you like
		# For example, when parsing raw_data, you may create several Node objects.  
		# Then you can store these objects into self.nodes.  
		# Finally, add to nd_dict by {key(index): value(corresponding node)}
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = []
        self.nd_dict = dict()  # key: index, value: the correspond node

        #buildMaze:
        for i in self.raw_data:
            curNode = Node(int(i[0]))
            
            self.nodes.append(curNode)
            self.nd_dict[curNode.index] = curNode
            
        for i in self.nodes:
            for j in range(1,5):
                if not pandas.isna(self.raw_data[i.index-1][j]):
                    #print (i.index, j, end="\n")
                    
                    i.setSuccessor(self.nd_dict[int(self.raw_data[i.index-1][j])],j ,int(self.raw_data[i.index-1][4+j]))

    def getStartPoint(self):
        if (len(self.nd_dict) < 2):
            print("Error: the start point is not included.")
            return 0
        return self.nd_dict[1]

    def getNodeDict(self):
        return self.nd_dict

    def BFS(self, nd):
        # TODO : design your data structure here for your algorithm
        q = queue.Queue()
        q.put(nd)
        lastNode = Node()
        flag = 0
        while(flag == 0): # flag == 1 means that all adjacent nodes are visited
            tmpNode = q.get()
            tmpNode.visited = True
            flag = 1
            for i in tmpNode.Successors:
                if (i[0].visited == False):
                    q.put(i[0])
                    flag = 0
                    i[0].pred = tmpNode
            if flag == 1:
                lastNode = tmpNode
        while (lastNode != nd):
            print(lastNode.index, end = " ")
            lastNode = lastNode.pred
        print(nd.index, end = "\n")
        # Tips : return a sequence of nodes from the node to the nearest unexplored deadend
        return None

    def BFS_2(self, nd_from, nd_to):
        # TODO : similar to BFS but with fixed start point and end point
        q = queue.Queue()
        q.put(nd_from)
        flag = 0
        while flag == 0:
            
            tmpNode = q.get()
            tmpNode.visited = True
            for i in tmpNode.Successors:
                if (i[0].visited == False):
                    q.put(i[0])
                    if i[0] == nd_to:
                        flag = 1
                    i[0].pred = tmpNode
        ans = []
        curNode = nd_to
        while(curNode != nd_from):
            
            ans.append(curNode)
            curNode = curNode.pred
        ans.append(nd_from)
        ans.reverse()
        # Tips : return a sequence of nodes of the shortest path
        return ans

    def getAction(self, car_dir, nd_from, nd_to):
        # TODO : get the car action
        # Tips : return an action and the next direction of the car if the nd_to is the Successor of nd_from
		# If not, print error message and return 0
        if not nd_from.isSuccessor(nd_to):
            print("two nodes aren't connected!!")
            return 0
        else:
            next_dir = nd_from.getDirection(nd_to)
            if car_dir == 1:
                if next_dir == 1:
                    return 'f'
                elif next_dir == 2:
                    return 'b'
                elif next_dir == 3:
                    return 'l'
                elif next_dir == 4:
                    return 'r'
            elif car_dir == 2:
                if next_dir == 1:
                    return 'b'
                elif next_dir == 2:
                    return 'f'
                elif next_dir == 3:
                    return 'r'
                elif next_dir == 4:
                    return 'l'
            elif car_dir == 3:
                if next_dir == 1:
                    return 'r'
                elif next_dir == 2:
                    return 'l'
                elif next_dir == 3:
                    return 'f'
                elif next_dir == 4:
                    return 'b'
            elif car_dir == 4:
                if next_dir == 1:
                    return 'l'
                elif next_dir == 2:
                    return 'r'
                elif next_dir == 3:
                    return 'b'
                elif next_dir == 4:
                    return 'f'
        

    def getActions(self, nodes):
        # TODO : given a sequence of nodes, return the corresponding action sequence
        # Tips : iterate through the nodes and use getAction() in each iteration
        ans = []
        ans.append('f')
        car_dir = nodes[0].getDirection(nodes[1])
        for i in range(1,len(nodes)-1):
            ans.append(self.getAction(car_dir, nodes[i], nodes[i+1]))
            car_dir = nodes[i].getDirection(nodes[i+1])
        return ans

    def actions_to_str(self, acti1ons):
        # cmds should be a string sequence like "fbrl....", use it as the input of BFS checklist #1
        cmd = "fbrls"
        cmds = ""
        for action in actions: cmds += cmd[action-1]
        print(cmds)
        return cmds

    def strategy(self, nd):
        return self.BFS(nd)

    def strategy_2(self, nd_from, nd_to):
        return self.BFS_2(nd_from, nd_to)

maze = Maze("maze (3).csv")
start = int(input("Start node:"))
end = int(input("End node:"))
nodes = maze.BFS_2(maze.nd_dict[start],maze.nd_dict[end])
print(maze.getActions(nodes))


#hahahaha