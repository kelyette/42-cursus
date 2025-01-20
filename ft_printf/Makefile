CC         := cc
CCFLAGS    := -Wall -Wextra -Werror -g

AR         := ar
ARFLAGS    := rcs

LFTDIR     := libft
LIBFTA     := $(LFTDIR)/libft.a

SRCDIR     := src
OBJDIR     := target
INCLDIR     = include

SRC        := ft_printf.c parser.c \
			  format_int.c format_char.c format_misc.c format_utils.c
OBJ        := $(SRC:%.c=$(OBJDIR)/%.o)
SRC        := $(SRC:%=$(SRCDIR)/%)

NAME        = libftprintf.a

ifdef ULIMIT
	CCFLAGS += -D'ULIMIT=$(ULIMIT)'
endif

all: $(NAME)

$(NAME): $(LIBFTA) $(OBJ)
	cp $< $@
	$(AR) $(ARFLAGS) $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -I$(LFTDIR) -I$(INCLDIR) -o $@ -c $<

$(LIBFTA):
	$(MAKE) -C $(dir $@)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME) | test.c
	$(CC) $(CCFLAGS) test.c $< -o out -g -I$(INCLDIR) -I$(LFTDIR)

.PHONY: all so clean fclean re test
