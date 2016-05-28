'''pybot starts by doing a shell call to start smashbot, then it tries looping to read states and write actions
if things constally loops, reading gamestate from a file, and outputting actions
to another file.
'''
import os
import numpy as np

def start_smashbot():
    os.system("./smashbot")

def get_frame():
    f = open('curframe.txt', 'r')
    #Test this
    new_frame = int(f.read())
    print('new frame is ')
    print(new_frame)
    return new_frame

def get_inputs(gamestate,prev_inputs):
    #Jab
    inputs = np.zeros(14)
    if gamestate % 2 == 0:
        inputs[0] = 1
    return inputs

def get_gamestate():
    f = open('curframe.txt', 'r')
    #Test this
    gamestate = int(f.read())
    print('gamestate is ')
    print(gamestate)
    return gamestate

if __name__=="__main__":
    start_smashbot()
    cur_frame = 0 
    prev_inputs = np.zeros(14)
    while True:
        #Check for new frame:
        new_frame = get_frame()
        if new_frame > cur_frame:
            #Get gamestate:
            game_state = get_gamestate()
            #Get input
            new_input = get_inputs(game_state,prev_inputs)
            #Write input
            np.savetxt('inputs.out', x, delimiter=',') 
            #Write new_frame
            fileloc = 'pyframe.txt'
            with open(fileloc,'w') as f:
                f.write(str(new_frame))
            cur_frame = new_frame  
            prev_inputs = new_input
