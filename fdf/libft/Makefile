CC = cc
AR = ar

CCWFLAGS = -Wall -Wextra -Werror -g -fPIC
ARFLAGS = rcs

STATICDIR = target_static
SHAREDDIR = target_shared
OBJDIR := $(STATICDIR)

SRC := chrop integer io ischr mem_copy mem_set mem_simple str_copy str_edit str_index str_simple str_comb
SRC := $(foreach src,$(SRC),ft_$(src).c)
BONUSSRC := lst_iter lst_manage lst_simple
BONUSSRC := $(foreach src,$(BONUSSRC),ft_$(src).c)
BONUSSRC += get_next_line.c format_char.c format_int.c format_misc.c format_utils.c \
			parser.c ft_printf.c

OBJSTATIC := $(addprefix $(STATICDIR)/,$(SRC:.c=.o))
OBJSHARED = $(addprefix $(SHAREDDIR)/,$(SRC:.c=.o) $(BONUSSRC:.c=.o))
BONUSOBJ = $(addprefix $(STATICDIR)/,$(BONUSSRC:.c=.o))

NAME := libft.a
NAME = libft

INSTALLDIR = $(HOME)/libs

TESTSRC = test.c
TESTEXE = test
DEVFLAGS = -O0 -fsanitize=address

ifeq ($(x86),1)
	CCWFLAGS += -arch x86_64
endif
ifeq ($(arm64),1)
	CCWFLAGS += -arch arm64
endif

all: $(NAME).a
so: $(NAME).so

$(NAME).a: $(OBJSTATIC)
	$(AR) $(ARFLAGS) $@ $^

$(NAME).so: OBJDIR := $(SHAREDDIR)
$(NAME).so: $(OBJSHARED)
	$(CC) $(CCWFLAGS) -shared -o $(NAME).so $^

$(STATICDIR)/%.o $(SHAREDDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CCWFLAGS) $(OBJCCFLAGS) -c $< -o $@

bonus: $(NAME).a $(BONUSOBJ)
	$(AR) $(ARFLAGS) $< $(BONUSOBJ)

bonus-so: OBJSHARED += $(BONUSOBJ)
bonus-so: $(NAME).so

clean:
	rm -rf $(STATICDIR) $(SHAREDDIR)

fclean: clean
	rm -f $(NAME).a $(NAME).so

re: fclean all

test: $(NAME).a $(TESTSRC)
	$(CC) $(CCFLAGS) $(DEVFLAGS) -o $(TESTEXE) $(TESTSRC) $(NAME).a

install: install-a
install-%: $(NAME).%
	@echo "installing $< to" $(INSTALLDIR)
	install -m 644 $< $(INSTALLDIR)

.PHONY: all a so bonus test clean fclean re
