#Place this script in the directory with the .jpg_color_edh_entropy files and call it
import os
files = os.listdir(os.getcwd())
files = [x for x in files if x.endswith(".jpg_color_edh_entropy")]
num_train = int(0.75*len(files))
num_test = int(0.25*len(files))
ctr = 0;
for filename in files:
	arr = []
	with open(filename) as file:
		lines = file.readlines()
		os.remove(filename)
		for line in lines:
			for x in map(float,line.split()):
				arr.append(x)
	if(ctr<num_train):
		with open("train","a") as file_new:
			file_new.writelines("%f " %item for item in arr)
			file_new.writelines("\n")
	else:
		with open("test","a") as file_new:
				file_new.writelines("%f " %item for item in arr)
				file_new.writelines("\n")
	ctr+=1