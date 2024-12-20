CC         := cc
CCFLAGS    := -Wall -Wextra -Werror -g

AR         := ar
ARFLAGS    := rcs

LFTDIR     := libft
LIBFTA     := $(LFTDIR)/libft.a

SRCDIR     := src
SHAREDDIR  := target_shared
STATICDIR  := target_static
OBJDIR     := $(STATICDIR)
INCLDIR     = include

SRC        := ft_printf.c ft_parsers.c ft_format_utils.c ft_format_int.c ft_format_uint.c ft_format_float.c ft_format_char.c ft_format_str.c ft_format_counter.c
STATICOBJ  := $(SRC:%.c=$(STATICDIR)/%.o)
SHAREDOBJ  := $(SRC:%.c=$(SHAREDDIR)/%.o)
SRC        := $(SRC:%=$(SRCDIR)/%)

NAME        = libftprintf.a
NAME        = libftprintf

ifdef ULIMIT
	CCFLAGS += -D'ULIMIT=$(ULIMIT)'
endif

all: $(NAME).a

so: $(NAME).so

$(NAME).a: $(LIBFTA) $(STATICOBJ)
	cp $< $@
	$(AR) $(ARFLAGS) $@ $(STATICOBJ)

$(NAME).so: OBJFLAGS += -fPIC
$(NAME).so: OBJDIR := $(SHAREDDIR)
$(NAME).so: $(SHAREDOBJ)
	$(CC) $(CCFLAGS) -shared -L$(LFTDIR) -lft -I$(LFTDIR) -I$(INCLDIR) -o $@ $^

$(STATICDIR)/%.o $(SHAREDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(OBJFLAGS) -I$(LFTDIR) -I$(INCLDIR) -o $@ -c $<

$(LIBFTA):
	$(MAKE) -C $(dir $@)

test: $(NAME).so
	$(CC) $(CCFLAGS) -L. -lftprintf -I$(INCLDIR) test.c -o out

clean:
	rm -rf $(SHAREDDIR) $(STATICDIR)

fclean: clean
	rm -f $(NAME).a $(NAME).so

re: fclean all

.PHONY: all so clean fclean re test
