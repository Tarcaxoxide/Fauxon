PROJECT_NAME = Fauxon

CC := g++
LD := $(CC)

ARGDIR=args
LDFLAGS = -static -Bsymbolic

SRCDIR := source
OBJDIR := build
BUILDDIR = build
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%_cpp.o, $(SRC))
DIRS = $(wildcard $(SRCDIR)/*)

$(OBJDIR)/%_cpp.o:$(SRCDIR)/%.cpp $(ARGDIR)/%.arg
	mkdir -p $(@D)
	${CC} -o $@ -c $< ${shell cat $(ARGDIR)/$(*).arg}

$(BUILDDIR)/$(PROJECT_NAME).exe: $(OBJS)
	${LD} $(LDFLAGS) -o $@ $^ -ljsoncpp


.PHONY: compile clean run test push

compile: $(BUILDDIR)/$(PROJECT_NAME).exe

clean:
	rm -frv $(BUILDDIR)/*

run: compile
	./$(BUILDDIR)/$(PROJECT_NAME).exe

push: compile clean
	git add .
	git commit -am "$(shell date)" 
	git push "https://loganer%40vivaldi.net:$(shell cat ../git_token.txt)@github.com/Tarcaxoxide/$(PROJECT_NAME).git"