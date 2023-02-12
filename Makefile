push:
	git add .
	git commit -am "$(shell date)" 
	git push "https://loganer%40vivaldi.net:$(shell cat ../git_token.txt)@github.com/Tarcaxoxide/Fauxon.git"


shell:
	deno run -A Shell.ts

test:
	deno run -A Run.ts test.txt


