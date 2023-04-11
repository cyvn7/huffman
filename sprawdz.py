from filecmp import cmp
from colorama import Fore, Back, Style

for i in range(int(input())):
	nazwy=input().split(" ")
	nazwa="dane/"+nazwy[0]
	nazwa2="dane/"+nazwy[1]
	if(cmp(nazwa,nazwa2)):
		print(Fore.GREEN + "Pliki",nazwa[5:],"oraz",nazwa2[5:],"są identyczne")
	else:
		print(Fore.RED + "Pliki",nazwa[5:],"oraz",nazwa2[5:],"NIE są zgodne")
