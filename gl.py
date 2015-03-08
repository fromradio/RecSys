import graphlab as gl

def main():
	gl.canvas.set_target('ipynb')
	train_file='u.data'
	sf = gl.SFrame.read_csv(train_file,header=False,delimiter='\t',verbose=False)
	sf.rename({'X1':'user_id','X2':'song_id','X3':'listen_count','X4':'time'}).show()
if __name__=='__main__':
	main()