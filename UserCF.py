from read import *
import math
from operator import itemgetter, attrgetter

def UserSimilarity(train):
	# build inverse tatble for iterm_users
	item_users = dict()
	for u, items in train.items():
		for i in items.keys():
			if i not in item_users:
				item_users[i] = set()
			item_users[i].add(u)
	C = dict()
	N = dict()
	for i, users in item_users.items():
		for u in users:
			if N.has_key(u):
				N[u] += 1
			else:
				N[u] = 1
			if C.has_key(u):
				pass
			else:
				C[u] = {}
			for v in users:
				if u == v:
					continue
				if C[u].has_key(v):
					C[u][v] += 1
				else:
					C[u][v] = 1
	W = dict()
	for u, related_users in C.items():
		W[u] = dict()
		for v, cuv in related_users.items():
			W[u][v] = cuv / math.sqrt(N[u]*N[v])
	return W

def Recommend(user,train,W,K):
	rank = dict()
	interacted_items = train[user].keys()
	l = sorted(W[user].items(),key=itemgetter(1),reverse=True)
	for v, wuv in l[0:K]:
		for i, rvi in train[v].items():
			if i in interacted_items:
				continue
			if not rank.has_key(i):
				rank[i] = 0
			rank[i] += wuv * rvi
	return rank

def main():
	data = ReadData("test.base")
	print data
	idata = ImplicitData(data)
	print idata
	W = UserSimilarity(idata)
	print W
	print Recommend('1',idata,W,3)

if __name__=='__main__':
	main()