import string
import random
def generuj(ileZnakow,ileLinii):
	znaki=string.ascii_letters+string.digits+string.punctuation
	for i in range(ileLinii):
		ciag=""
		for j in range(ileZnakow):
			ciag+=random.choice(znaki)
		print(ciag)
		
a,b=input().split()
generuj(int(a),int(b))
