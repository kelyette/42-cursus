CC = cc
AR = ar

CCWFLAGS = -Wall -Wextra -Werror -g
ARFLAGS = rcs

INCL = libft.h
SRC := chrop integer io ischr mem_copy mem_set mem_simple str_copy str_edit str_index str_simple str_comb
SRC := $(foreach src,$(SRC),ft_$(src).c)
BONUSSRC := lst_iter lst_manage lst_simple
BONUSSRC := $(foreach src,$(BONUSSRC),ft_$(src).c)
STATICDIR = target_static
SHAREDDIR = target_shared
OBJDIR := $(STATICDIR)
OBJSTATIC := $(addprefix $(STATICDIR)/,$(SRC:.c=.o))
OBJSHARED = $(addprefix $(SHAREDDIR)/,$(SRC:.c=.o) $(BONUSSRC:.c=.o))
BONUSOBJ = $(addprefix $(STATICDIR)/,$(BONUSSRC:.c=.o))

NAME := libft.a
NAME := libft

INSTALLDIR = ~/libs

TESTSRC = test.c
TESTEXE = test
DEVFLAGS = -O0 -fsanitize=address

UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
	CC = clang
endif

all: $(NAME).a
so: $(NAME).so

$(NAME).a: $(OBJSTATIC)
	$(AR) $(ARFLAGS) $@ $^

$(NAME).so: OBJCCFLAGS = -fPIC
$(NAME).so: OBJDIR := $(SHAREDDIR)
$(NAME).so: $(OBJSHARED)
	$(CC) $(CCWFLAGS) -shared -o $(NAME).so $^

$(STATICDIR)/%.o $(SHAREDDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CCWFLAGS) $(OBJCCFLAGS) -c $< -o $@

bonus: $(NAME).a $(BONUSOBJ)
	$(AR) $(ARFLAGS) $< $(BONUSOBJ)

clean:
	rm -rf $(STATICDIR) $(SHAREDDIR)

fclean: clean
	rm -f $(NAME).a $(NAME).so

re: fclean all

test: $(NAME) $(TESTSRC)
	$(CC) $(CCFLAGS) $(DEVFLAGS) -o $(TESTEXE) $(TESTSRC) $(NAME)

install: $(NAME).a
	@echo "installing to" $(INSTALLDIR)
	@mkdir -p $(INSTALLDIR)
	cp $< $(INSTALLDIR)/$<
	cp $(INCL) $(INSTALLDIR)/$(INCL)

.PHONY: all a so bonus test clean fclean re
