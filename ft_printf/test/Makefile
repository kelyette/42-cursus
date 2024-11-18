CC = clang
PY3 = python3
SHELL = /bin/bash

CCFLAGS = -Werror -Wall -Wextra -O0 -g

ROOTDIR = ..
TRGTDIR = target
LIBFTDIR ?= $(ROOTDIR)/libft

LIB = $(ROOTDIR)/libftprintf.a

LIBFTFLAGS = -L$(LIBFTDIR) -I$(LIBFTDIR) -lft
LIBFLAGS = -I$(ROOTDIR)/include

SRC = test.c $(LIB)

EXEC ?= $(TRGTDIR)/test000
EXECN = $(lastword $(subst test, ,$(EXEC)))

SYSRES = $(EXEC)_sys.txt
USRRES = $(EXEC)_usr.txt

VENVPACKAGE = venv
VENVDIR = venv
VENVCMD = $(PY3) -m $(VENVPACKAGE) $(VENVDIR)

LOGFILE = result.txt

ifeq (, $(shell command -v timeout 2> /dev/null))
	TIMEOUTC = timeout 2
endif

ifeq ($(LEAKS),1)
	LK = leaks -atExit -quiet -- 
endif
ifeq ($(ASAN),1)
	CCFLAGS += -fsanitize=address
endif

OS := $(shell uname -s)
ifeq ($(OS),Darwin)
	MACROERRFLAG =	 -fmacro-backtrace-limit=0
	BUILDCMD = $(CC) $(CCFLAGS) -o $(EXEC) $(LIBFTFLAGS) $(LIBFLAGS) $(SRC)
else ifeq ($(OS),Linux)
	CC = clang
	BUILDCMD = $(CC) $(CCFLAGS) -o $(EXEC) $(SRC) $(LIBFLAGS) $(LIBFTFLAGS)
else
	BUILDCMD = $(CC) -Werror -o $(EXEC) $(LIBFTFLAGS) $(LIBFLAGS) $(SRC)
endif

ifdef VVARS
	VVARSPARAM = -D'VARS=$(VVARS)'
endif

all: build

checkoutput: runexec $(LOGFILE)
	@echo "--- Checking diff..."
	@cp .varfile $(EXEC)_var.txt
	@echo -n "" > .varfile
	sdiff -w 60 $(USRRES) $(SYSRES) | \
		cut -c1-31,45- | \
		awk 'BEGIN {v=0} substr($$0, 30, 1) == "|"{ printf("$(EXECN):%-3d %s\n", v, $$0) } {v++}' | \
		cut -c1-37,40- | \
		tee -a $(LOGFILE)

runexec: build
	@echo "--- Running test job..."
	touch $(USRRES) $(SYSRES)
	$(TIMEOUTC) ./$(EXEC) | awk 'BEGIN {t = 0} /---/ {t++; next} {if (t) {print $0 >> "$(SYSRES)"} else {print $0 >> "$(USRRES)"}}'

build: $(LIB) $(TESTOBJ)
	@echo "--- Building libftprintf..."
	$(MAKE) -C $(ROOTDIR) ULIMIT=9999 THROWERR=1
	@mkdir -p $(TRGTDIR)
	$(BUILDCMD) -D'FORMAT="$(VFORMAT)"' $(VVARSPARAM)

stest:
	$(MAKE) -C $(ROOTDIR) all ULIMIT=9999 THROWERR=1
	@mkdir -p $(TRGTDIR)
	$(BUILDCMD) -D'TEST'
	$(TIMEOUTC) ./$(EXEC)

r: clean
	@echo "n       | format     | usr           | sys" > $(LOGFILE)
	$(VENVDIR)/bin/python test.py $(PYARGS)

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
