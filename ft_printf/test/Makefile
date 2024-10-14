CC = clang
PY3 = python3

PRJTDIR = ..
TRGTDIR = target
LIBFTDIR ?= $(HOME)/libs

LIB = $(PRJTDIR)/libftprintf.a

LIBFTFLAGS = -L$(LIBFTDIR) -I$(LIBFTDIR) -lft
LIBFLAGS = -I$(PRJTDIR)/include

SRC = test.c $(LIB)

EXEC ?= $(TRGTDIR)/test

SYSRES = $(EXEC)_sys.txt
USRRES = $(EXEC)_usr.txt

VENVPACKAGE = venv
VENVDIR = venv
VENVCMD = $(PY3) -m $(VENVPACKAGE) $(VENVDIR)

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

ifdef VVARS
	VVARSPARAM = -D'VARS=$(VVARS)'
endif

all: checkoutput

checkoutput: runexec
	@echo "--- Checking diff..."
	diff -U 3 $(USRRES) $(SYSRES) | tee -a $(LOGFILE)

runexec: build
	@echo "--- Running test job..."
	@echo '$(VFORMAT)\n$(VVARS)' | tee $(SYSRES) | tee $(USRRES)
	./$(EXEC) | awk 'BEGIN {t = 0} /---/ {t++; next} {if (t) {print $0 >> "$(SYSRES)"} else {print $0 >> "$(USRRES)"}}'

build: $(LIB) $(TESTOBJ)
	@echo "--- Building libftprintf..."
	$(MAKE) -C $(PRJTDIR)
	@mkdir -p $(TRGTDIR)
	@echo 
	$(BUILDCMD) -D'FORMAT="$(VFORMAT)"' $(VVARSPARAM)

r: fclean
	$(VENVDIR)/bin/python test.py

$(VENVDIR):
	rm -rf $@
	$(VENVCMD)
	$(VENVDIR)/bin/pip install tqdm

clean:
	rm -rf $(TRGTDIR)

oclean:
	rm -f $(LOGFILE)

fclean: clean oclean

.PHONY: all checkoutput runexec build r tvenv clean oclean fclean
