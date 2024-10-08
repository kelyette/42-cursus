CC := cc
CCFLAGS := -Wall -Wextra -Werror
LBDIR := $(HOME)/libs
LBFLAGS := -L$(LBDIR) -lft

AR := ar
ARFLAGS := rcs

SRCDIR := src
OBJDIR := target
SRC := ft_printf.c ft_parser.c ft_utils.c ft_format_utils.c ft_format_char.c ft_format_hex.c ft_format_int.c
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
SRC := $(SRC:%=$(SRCDIR)/%)

INCLDIR = include

LIB = libftprintf.a

TESTDIR = test
TESTSRC = $(TESTDIR)/test.c
TESTEXEC = $(TESTDIR)/test
DEVFLAGS = -g -O0 -fsanitize=address

all: $(LIB)

dev: OBJFLAGS = -g -O0
dev: $(TESTEXEC)

$(TESTEXEC): $(SRC) $(TESTSRC)
	$(CC) $(CCFLAGS) $(DEVFLAGS) -L$(LBDIR) -I$(LBDIR) -lft -I$(INCLDIR) -o $(TESTEXEC) $(TESTSRC) $(SRC)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) $(OBJFLAGS) -I$(LBDIR) -I$(INCLDIR) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIB)

dclean: clean
	rm -f $(TESTEXEC)

re: fclean all

.PHONY: all clean fclean re dev
