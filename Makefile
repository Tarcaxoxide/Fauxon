PROJECT_NAME = Fauxon

CC := g++
LD := $(CC)

INCDIR=header
CFLAGS = -I$(INCDIR) -Werror -fshort-wchar -mno-red-zone -fmax-errors=1
LDFLAGS = -static -Bsymbolic

SRCDIR := source
OBJDIR := build
BUILDDIR = build
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%_cpp.o, $(SRC))
DIRS = $(wildcard $(SRCDIR)/*)

$(OBJDIR)/%_cpp.o:$(SRCDIR)/%.cpp
	mkdir -p $(@D)
	${CC} $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/$(PROJECT_NAME).exe: $(OBJS)
	${LD} $(LDFLAGS) -o $@ $^


.PHONY: compile clean run test push

compile: $(BUILDDIR)/$(PROJECT_NAME).exe

clean:
	rm -frv $(BUILDDIR)/*

run: compile
	time(./$(BUILDDIR)/$(PROJECT_NAME).exe $(TESTFILE))

test: tests/Test.sh
	./$<

push: compile clean
	git add .
	git commit -am "$(shell date)" 
	git push "https://loganer%40vivaldi.net:$(shell cat ../git_token.txt)@github.com/Tarcaxoxide/$(PROJECT_NAME).git"