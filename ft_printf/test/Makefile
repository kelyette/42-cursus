CC = clang
PY3 = python3
SHELL = /bin/bash

CCFLAGS = -Werror -Wall -Wextra -O0 -g

ROOTDIR = ..
TRGTDIR = target

LIB = $(ROOTDIR)/libftprintf.a

LIBFLAGS = -I$(ROOTDIR)/include -I$(ROOTDIR)/libft

SRC = test.c $(LIB)

EXEC ?= out
EXECN = $(lastword $(subst test, ,$(EXEC)))

SYSRES = $(EXEC)_sys.txt
USRRES = $(EXEC)_usr.txt
RESDIF = $(EXEC)_diff.txt

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
	BUILDCMD = $(CC) $(CCFLAGS) -o $(EXEC) $(LIBFLAGS) $(SRC)
else ifeq ($(OS),Linux)
	CC = clang
	BUILDCMD = $(CC) $(CCFLAGS) -o $(EXEC) $(SRC) $(LIBFLAGS)
else
	BUILDCMD = $(CC) -Werror -o $(EXEC) $(LIBFLAGS) $(SRC)
endif

ifdef VVARS
	VVARSPARAM = -D'VARS=$(VVARS)'
endif

ifdef CONTROL
	CONTROLFLAG = -D'CONTROL'
endif
all: build

checkoutput: runexec $(LOGFILE)
	@echo "- Checking diff..."
	@cp .varfile $(EXEC)_var.txt
	@echo -n "" > .varfile
	sdiff -a -w 100 $(USRRES) $(SYSRES) | tee $(RESDIF)
	sdiff -ad -w 60 $(USRRES) $(SYSRES) | \
		cut -c1-31,45- | \
		awk 'BEGIN {v=0} substr($$0, 30, 1) == "|"{ printf("$(EXECN):%-3d %s\n", v, $$0) } {v++}' | \
		cut -c1-37,40- | \
		tee -a $(LOGFILE)

runexec: build
	@echo "- Running test job..."
	rm -f $(USRRES) $(SYSRES)
	touch $(USRRES) $(SYSRES)
	$(TIMEOUTC) ./$(EXEC) | iconv -c -f UTF-8 -t ASCII//TRANSLIT | awk 'BEGIN {t = 0} /---/ {t++; next} {if (t) {print $0 >> "$(SYSRES)"} else {print $0 >> "$(USRRES)"}}'

build: $(LIB) $(TESTOBJ)
	@mkdir -p $(TRGTDIR)
	$(BUILDCMD) $(CONTROLFLAG) -D'FORMAT="$(VFORMAT)"' $(VVARSPARAM)

$(LIB):
	@echo "- Building libftprintf..."
	$(MAKE) -C $(dir $(LIB)) all ULIMIT=9999

stest:
	$(MAKE) -C $(ROOTDIR) all ULIMIT=9999
	@mkdir -p $(TRGTDIR)
	$(BUILDCMD) -D'TEST'
	$(TIMEOUTC) ./$(EXEC)

r: clean
	@echo "n       | format     | usr           | sys" > $(LOGFILE)
	$(MAKE) -C $(dir $(LIB)) all ULIMIT=9999
	$(VENVDIR)/bin/python test.py $(PYARGS)

$(LOGFILE):
	touch $@

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
