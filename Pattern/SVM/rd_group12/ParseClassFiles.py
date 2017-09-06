#Place this script in the directory with the .jpg_color_edh_entropy files and call it
import os
files = os.listdir(os.getcwd())
files = [x for x in files if x.endswith(".txt")]


for filename in files:
	with open(filename) as file:
		lines = file.readlines()
		os.remove(filename)
		num_train = int(0.75*len(lines))
		num_test = int(0.25*len(lines))
		print num_train," ",num_test
		ctr = 0;
		for line in lines:
			arr = []
			for x in map(float,line.split()):
				arr.append(x)
			if(ctr<num_train):
				with open("train"+filename[5:6],"a") as file_new:
					file_new.writelines("%f " %item for item in arr)
					file_new.writelines("\n")
			else:
				with open("test"+filename[5:6],"a") as file_new:
						file_new.writelines("%f " %item for item in arr)
						file_new.writelines("\n")
			ctr+=1
