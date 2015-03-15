from UserCF import *
from SplitData import *
# import matplotlib.pyplot as plt

def Recall(train,test,W,N,K):
	hit = 0
	all = 0
	i = 0
	for user in train.keys():
		if not test.has_key(user):
			continue
		tu = test[user]
		rank = Recommend(user,train,W,K)
		s = sorted(rank.items(),key=itemgetter(1),reverse=True)[0:N]
		for item, pui in s:
			if item in tu:
				hit += 1
		all += len(tu)
		i = i+1
	print "there are",i,"users"
	return hit/(all*1.0)

def Precision(train,test,W,N,K):
	hit = 0
	all = 0
	for user in train.keys():
		if not test.has_key(user):
			continue
		tu = test[user]
		tu = test[user]
		rank = Recommend(user,train,W,K)
		s = sorted(rank.items(),key=itemgetter(1),reverse=True)[0:N]
		for item, pui in s:
			if item in tu:
				hit += 1
		all += N
	return hit/(all*1.0)


# {user_id:{item_id:score}}
# N: top N item
# K: size of neighborhood
def main():
	# test = ReadImplicitData('u2.test')
	# train = ReadImplicitData('u2.base')
	M = 8
	k = 2
	seed = 10
	data = ReadData("Newexample20.txt")
	(traindata,testdata) = SplitData(data,M,k,seed)
	train = ImplicitData(traindata)
	test = ImplicitData(testdata)

	W = UserSimilarity(train)
	R = []
	P = []
	# for K in range(10,41):
	# 	r = Recall(train,test,W,10,K)
	# 	R.append(r)
	# 	print "recall(K=%d) is: %f"%(K,r)
	# 	p = Precision(train,test,W,10,K)
	# 	P.append(p)
	# 	print "precision(K=%d) is: %f"%(K,p)
	# for N in range(3,13):
	# 	r = Recall(train,test,W,N,20)
	# 	R.append(r)
	# 	print "recall(N=%d) is: %f"%(N,r)
	# 	p = Precision(train,test,W,N,20)
	# 	P.append(p)
	# 	print "precision(N=%d) is: %f"%(N,p)
	# 	F = 2*p*r/(p+r)
	# 	print "F-value: %f"%F
	# # print "Recall",R
	# # print "Precision",P
	# plt.plot(R,P)
	# plt.ylabel('precision')
	# plt.xlabel('recall')
	# plt.show()
	print Recall(train,test,W,10,20)
	print Precision(train,test,W,10,20)
if __name__ == '__main__':
	main()