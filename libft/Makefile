CC = cc
AR = ar

CCFLAGS = -Wall -Wextra -Werror
ARFLAGS = rcs

INCL = libft.h
SRC := chrop integer io ischr mem_copy mem_set mem_simple str_copy str_edit str_index str_simple
SRC := $(foreach src,$(SRC),ft_$(src).c)
BONUSSRC := lst_iter lst_manage lst_simple bonus
BONUSSRC := $(foreach src,$(BONUSSRC),ft_$(src).c)
OBJDIR = target
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
BONUSOBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(BONUSSRC))

LIB = libft.a

INSTALLDIR = ~/libs

TESTSRC = test.c
TESTEXE = test
DEVFLAGS = -g -O0 -fsanitize=address

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)

$(OBJDIR)/%.o: %.c $(INCL)
	@mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

bonus: $(BONUSOBJ) $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ) $(BONUSOBJ)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIB)

re: fclean all

test: $(LIB) $(TESTSRC)
	$(CC) $(CCFLAGS) $(DEVFLAGS) -o $(TESTEXE) $(TESTSRC) $(LIB)

install: $(LIB)
	@echo "installing to" $(INSTALLDIR)
	@mkdir -p $(INSTALLDIR)
	cp $< $(INSTALLDIR)/$<
	cp $(INCL) $(INSTALLDIR)/$(INCL)

.PHONY: all bonus test clean fclean re
