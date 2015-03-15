import graphlab as gl

def main():
	# gl.canvas.set_target('ipynb')
	# train_file='example.txt'
	train_file = '20_new.csv'
	sf = gl.SFrame.read_csv(train_file,header=False,delimiter='\t',verbose=False)
	sf.rename({'X1':'user_id','X2':'song_id','X3':'score'})
	(train_set,test_set) = sf.random_split(0.8,seed=1)
	popularity_model = gl.recommender.popularity_recommender.create(train_set,'user_id','song_id')
	# factorization_model = gl.factorization_recommender.create(train_set,'user_id','song_id',target='score',regularization=0.5,num_factors=64)
	item_sim_model = gl.item_similarity_recommender.create(train_set,'user_id','song_id')
	result = gl.recommender.util.compare_models(test_set,[popularity_model,item_sim_model],user_sample=0.05,metric='precision_recall')
	# result = gl.recommender.util.compare_models(test_set,[factorization_model,item_sim_model],metric='precision_recall')
	# result = gl.recommender.util.compare_models(test_set,[item_sim_model],user_sample=0.05,metric='precision_recall')
if __name__=='__main__':
	main()