import pandas as pd
import sys
import random

def DataPartition(input,train,test,num=8):
	trainf = open(train,"w+")
	testf = open(test,"w+")
	with open(input,"r") as f:
		for line in f:
			if random.randint(0,num-1) == 0:
				testf.write(line)
			else:
				trainf.write(line)
if __name__ =='__main__':
	if len(sys.argv) == 4:
		DataPartition(sys.argv[1],sys.argv[2],sys.argv[3])
	elif len(sys.argv) == 5:
		DataPartition(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4])
	else:
		sys.exit("Usage: %s input filename train filename test filename"%sys.argv[0])