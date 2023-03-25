C_FLAGS=-IHeaders -Ofast $(CFLAGS)
CC = clang++
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC = $(call rwildcard,Sources,*.cpp)
OBJS = $(patsubst Sources/%.cpp, Build/%.o, $(SRC))


Build/%.o:Sources/%.cpp
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -c $^ -o $@

Build/exe:$(OBJS)
	$(CC) $(C_FLAGS) -o $@ $^

.PHONY: compile clean push run

compile: Build/exe

clean:
	@rm -frv Build/*

push: clean compile
	git add .
	git commit -am "$(shell date)" 
	git push "https://loganer%40vivaldi.net:$(shell cat ../git_token.txt)@github.com/Tarcaxoxide/Fauxon.git"

run: Build/exe
	./$<
