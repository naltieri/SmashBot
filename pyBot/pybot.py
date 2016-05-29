'''pybot starts by doing a shell call to start smashbot, then it tries looping to read states and write actions
if things constally loops, reading gamestate from a file, and outputting actions
to another file.
'''
import os
import numpy as np

def start_smashbot():
	os.system("./smashbot")

def get_frame():
	failed_read = True
	while failed_read:
		try:
			f = open('curframe.txt', 'r')
			new_frame = int(f.read())
			failed_read = False 
		except: 
			0
	return new_frame

def get_inputs(gamestate,prev_inputs):
	#Jab
	inputs = np.zeros(1)
	if gamestate % 2 == 0:
		inputs[0] = 1
	return inputs.astype(int)

def get_gamestate():
	f = open('gamestate.txt', 'r')
	gamestate = int(f.read())
	print('gamestate is ')
	print(gamestate)
	return gamestate

def write_input(new_input):
	input_str = ''
	fileloc = 'inputs.txt'
	for i in range(len(new_input)):
		input_str += str(new_input[i])
	with open(fileloc,'w') as f:
		f.write(input_str)

def run_pybot():
	cur_frame = -1
	prev_inputs = np.zeros(1)
	while True:
		#Check for new frame:
		new_frame = get_frame()
		print('new frame is')
		print(new_frame)

		if new_frame > cur_frame:
			#Get gamestate:
			game_state = get_gamestate()
			#Get input
			new_input = get_inputs(game_state,prev_inputs)
			#Write input
			write_input(new_input)
			#Write new_frame
			fileloc = 'pyframe.txt'
			with open(fileloc,'w') as f:
				f.write(str(new_frame))
			cur_frame = new_frame  
			prev_inputs = new_input


if __name__=="__main__":
	#Writing initial files:
	fileloc = 'curframe.txt'
	with open(fileloc,'w') as f:
		f.write(str(-1))
	fileloc = 'gamestate.txt'
	with open(fileloc,'w') as f:
		f.write(str(-1))
	
	pid=os.fork()
	if pid:
		start_smashbot()
	else: 
		run_pybot()
	
