'''pybot starts by doing a shell call to start smashbot, then it tries looping to read states and write actions
if things constally loops, reading gamestate from a file, and outputting actions
to another file.
'''
import csv
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
	inputs = np.zeros(12)
	inputs = np.random.rand(12)
	return inputs

def get_gamestate():

	p1damage=[]
	p2damage=[]
	p1stock=[]
	p2stock=[]
	p1character=[]
	p2character=[]
	p1facing=[]
	p2facing=[]

	x1=[]
	x2=[]
	y1=[]
	y2=[]
	speedair1=[]
	speedair2=[]
	speedground1=[]
	speedground2=[]
	speedyself1=[]
	speedyself2=[]
	vxa1=[]
	vya1=[]
	vxa2=[]
	vya2=[]

	c1d_raw=[]
	c1a_raw=[]
	c1s_raw=[]
	c2d_raw=[]
	c2a_raw=[]
	c2s_raw=[]
	p1act=[]
	p1act_long=[]
	p1act_counter=[]
	p1act_frame=[]
	p1state=[]
	p2act=[]
	p2act_long=[]
	p2act_counter=[]
	p2act_frame=[]
	p2state=[]

	p1charge=[]
	p2charge=[]
	p1invul=[]
	p2invul=[]
	p1hitlag=[]
	p2hitlag=[]
	p1hitstun=[]
	p2hitstun=[]
	p1jumps=[]
	p2jumps=[]
	p1grounded=[]
	p2grounded=[]

	t=[]

	with open('gamestate.txt', 'rb') as csvfile:
		
		spamreader = csv.reader(csvfile, delimiter=',')

		for row in spamreader:
			
			t.append(float(row[0]))

			p1damage.append(float(row[3]))
			p2damage.append(float(row[4]))
			p1stock.append(float(row[5]))
			p2stock.append(float(row[6]))
			p1character.append(float(row[7]))
			p2character.append(float(row[8]))
			p1facing.append(float(row[9]))
			p2facing.append(float(row[10]))

			x1.append(float(row[15]))
			x2.append(float(row[17]))
			y1.append(float(row[16]))
			y2.append(float(row[18]))

			p1invul.append(float(row[25]))
			p2invul.append(float(row[26]))
			p1charge.append(float(row[27]))
			p2charge.append(float(row[28]))
			p1hitlag.append(float(row[29]))
			p2hitlag.append(float(row[30]))
			p1hitstun.append(float(row[31]))
			p2hitstun.append(float(row[32]))
			p1jumps.append(float(row[33]))
			p2jumps.append(float(row[34]))
			p1grounded.append(float(row[35]))
			p2grounded.append(float(row[36]))

			speedair1.append(float(row[37]))
			speedair2.append(float(row[38]))
			speedyself1.append(float(row[39]))
			speedyself2.append(float(row[40]))
			vxa1.append(float(row[41]))
			vxa2.append(float(row[42]))
			vya1.append(float(row[43]))
			vya2.append(float(row[44]))
			speedground1.append(float(row[45]))
			speedground2.append(float(row[46]))

			p1act.append(int(row[19], 16))
			actidx=int(row[19], 16)
			temp=np.zeros(382)
			temp[actidx]=1.0
			p1act_long.append(temp)
			p1act_counter.append(int(row[21]))
			p1act_frame.append(int(row[23]))
			p2act.append(int(row[20], 16))
			actidx=int(row[20], 16)
			temp=np.zeros(382)
			temp[actidx]=1.0
			p2act_long.append(temp)
			p2act_counter.append(int(row[22]))
			p2act_frame.append(int(row[24]))
			# c1a_raw.append(np.array(map(int, bin(int(row[-5], scale))[2:].zfill(num_of_bits))))

			#c1d_raw.append(np.array(map(int, bin(int(row[47], 10))[2:].zfill(32))))
			#c1a_raw.append(bin(int(row[48], 10))[2:].zfill(32))
			#c1s_raw.append(bin(int(row[49], 10))[2:].zfill(32))
			#c2d_raw.append(np.array(map(int, bin(int(row[50], 10))[2:].zfill(32))))
			#c2a_raw.append(bin(int(row[51], 10))[2:].zfill(32))
			#c2s_raw.append(bin(int(row[52], 10))[2:].zfill(32))
	
	p1total=[p1damage, p1stock, p1character, p1facing, x1, y1, speedair1, speedground1, speedyself1, vxa1, vya1, p1act_frame, p1charge, p1invul, p1hitlag, p1hitstun, p1jumps, p1grounded]

	p1total=np.asarray(p1total).T

	p1act_long=np.asarray(p1act_long)
	p1_state_total=np.hstack((p1total, p1act_long)).astype(np.float32)
	
	p2total=[p2damage, p2stock, p2character, p2facing, x2, y2, speedair2, speedground2, speedyself2, vxa2, vya2, p2act_frame, p2charge, p2invul, p2hitlag, p2hitstun, p2jumps, p2grounded]

	p2total=np.asarray(p2total).T

	p2act_long=np.asarray(p2act_long)
	p2_state_total=np.hstack((p2total, p2act_long)).astype(np.float32)
	
	gamestate = np.concatenate((np.asarray(t).astype(np.float32).flatten(),p1_state_total.flatten(),p2_state_total.flatten())).flatten()
	



	return gamestate

def write_input(new_input):
	fileloc = 'inputs.txt'
	with open(fileloc,'w') as f:	
		for i in range(len(new_input)):
			if i < 8:
				input_str = str(int(new_input[i]>0.9))+'\n'
				f.write(input_str)
			else:
				input_str = str(float(new_input[i]))+'\n'
				f.write(input_str)
			print(input_str)
				
	

def run_pybot():
	cur_frame = -1
	prev_inputs = np.zeros(12)
	while True:
		#Check for new frame:
		new_frame = get_frame()

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
	
