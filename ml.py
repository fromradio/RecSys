from UserCF import *

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
	test = ReadImplicitData('u2.test')
	train = ReadImplicitData('u2.base')
	W = UserSimilarity(train)
	print Recall(train,test,W,10,20)
	print Precision(train,test,W,10,20)
if __name__ == '__main__':
	main()