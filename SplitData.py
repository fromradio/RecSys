from UserCF import *
import random

def SplitData(data,M,k,seed):
	testdata = []
	traindata = []
	random.seed(seed)
	for d in data:
		if random.randint(0,M) == k:
			testdata.append(d) 
		else:
			traindata.append(d)
	return traindata,testdata

def main():
	M = 8
	k = 2
	seed = 3
	data = ReadData("test.base")
	(traindata,testdata) = SplitData(data,M,k,seed)
	print "traindata:",traindata
	print "testdata:",testdata

if __name__ == "__main__":
	main()
