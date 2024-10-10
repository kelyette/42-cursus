CC = cc

PRJTDIR = ..
TRGTDIR = target
LIBFTDIR = /home/kcsajka/libs

LIB = $(PRJTDIR)/libftprintf.a

LIBFTFLAGS = -L$(LIBFTDIR) -I$(LIBFTDIR) -lft
LIBFLAGS = -I$(PRJTDIR)/include

SRC = test.c $(LIB)

EXEC ?= $(TRGTDIR)/test

VFORMAT ?= %s
VVARS ?= "VVARS not specified"

SYSRES = $(EXEC)_sys.txt
USRRES = $(EXEC)_usr.txt

LOGFILE = result.txt

OS := $(shell uname -s)
ifeq ($(OS),Darwin)
	MACROERRFLAG =	 -fmacro-backtrace-limit=0
	BUILDCMD = $(CC) -Werror -o $(EXEC) $(LIBFTFLAGS) $(LIBFLAGS) $(SRC)
else ifeq ($(OS),Linux)
	CC = clang
	BUILDCMD = $(CC) -Werror -o $(EXEC) $(SRC) $(LIBFLAGS) $(LIBFTFLAGS)
else
	BUILDCMD = $(CC) -Werror -o $(EXEC) $(LIBFTFLAGS) $(LIBFLAGS) $(SRC)
endif

all: checkoutput

checkoutput: runexec
	@echo "--- Checking diff..."
	diff -U 3 $(USRRES) $(SYSRES) | tee -a $(LOGFILE)

runexec: build
	@echo "--- Running test job..."
	./$(EXEC) | awk 'BEGIN {t = 0} /---/ {t++; next} {if (t) {print $0 > "$(SYSRES)"} else {print $0 > "$(USRRES)"}}'

build: $(LIB) $(TESTOBJ)
	@echo "--- Building libftprintf..."
	$(MAKE) -C $(PRJTDIR)
	@mkdir -p $(TRGTDIR)
	@echo 
	$(BUILDCMD) -D'FORMAT="$(VFORMAT)"' -D'VARS=$(VVARS)'

clean:
	rm -rf $(TRGTDIR)

oclean:
	rm -f $(LOGFILE)

fclean: clean oclean
