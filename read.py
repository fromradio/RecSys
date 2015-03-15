def ReadData(filename):
	# filename contains the path of the data filename
	f = open(filename,"r")
	data = []
	for line in f:
		data.append(line.strip('\n').split('\t'))
	return data

def ImplicitData(data):
	idata = {}
	for d in data:
		if not idata.has_key(d[0]):
			idata[d[0]]={}
		idata[d[0]][d[1]] = float(d[2])
	return idata

def ReadImplicitData(filename):
	data = ReadData(filename)
	return ImplicitData(data)

def main():
	data = ReadData("u.data")
	idata = ImplicitData(data)
	print idata

if __name__ == '__main__':
	main()