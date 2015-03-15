import pandas as pd
import sys

def FileFiltering(input,output,s=' '):
	data = pd.read_csv(input,delimiter=r"\s+",header=None)
	usermap={}
	itemmap={}
	datamap={}
	iu=0
	it=0
	for user in data[0]:
		if not usermap.has_key(user):
			usermap[user]=iu
			iu = iu+1
	for item in data[1]:
		if not itemmap.has_key(item):
			itemmap[item]=it
			it = it+1

	f = open(output,'w+')
	lens = len(data[0])
	klens = len(data.keys())
	print "start writing"
	for i in range(0,lens):
		f.write(str(usermap[data[0][i]]))
		f.write('\t')
		f.write(str(itemmap[data[1][i]]))
		f.write('\t')
		for j in range(2,klens):
			f.write(str(data[j][i]))
			if j < klens-1:
				f.write('\t')
			else:
				f.write('\n')
	f.close()

def main():
	if len(sys.argv) == 3:
		FileFiltering(sys.argv[1],sys.argv[2])
	elif len(sys.argv) == 4:
		FileFiltering(sys.argv[1],sys.argv[2],sys.argv[3])
	else:
		sys.exit('Usage: %s input filename output filename'%sys.argv[0])
		

if __name__ == '__main__':
	main()