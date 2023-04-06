all:
	gcc src/huff.c src/kodowanie.c src/szyfruj.c src/flagi.c -o kod.huff

clean:
	rm *.huffman *.table
	
cleano:
	rm *.huff
