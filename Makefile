all:
	gcc src/huff.c src/kodowanie.c src/szyfruj.c src/flagi.c -o kod.huff

clean:
	rm *.huffman *.table
	
cleano:
	rm *.huff
	
testuj:
	./kod.huff a.txt
	./kod.huff a.txt.huffman
	@echo "\033[0;34m Plik kodujemy i dekodujemy \033[0;37m"
	./kod.huff -k b.txt -s
	./kod.huff -d b.txt.huffman -s
	@echo "\033[0;34m Plik kodujemy, szyfrujemy, dekodujemy i deszyfrujemy \033[0;37m"
	./kod.huff c.txt -s
	./kod.huff c.txt.huffman
	@echo "\033[0;34m Plik kodujemy, szyfrujemy i dekodujemy \033[0;37m"
	python3 sprawdz.py<generatorTestow/porownania.txt
