compile:
	rm -frv exe
	clang++ -Iinc src/*.cpp -o exe


push: compile
	git add .
	git commit -am "$(shell date)" 
	git push "https://loganer%40vivaldi.net:$(shell cat ../git_token.txt)@github.com/Tarcaxoxide/Fauxon.git"

run: compile
	./exe ./TestA.faux
	./exe ./TestB.faux
	./exe ./TestC.faux
