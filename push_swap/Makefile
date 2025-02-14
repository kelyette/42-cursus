CC          := clang
RM          := rm -rf

CCFLAGS     := -Wall -Wextra -Werror -g

LIBFTDIR    := libft
OBJDIR      := target

SRC         := push_swap.c operations.c stack.c utils.c sorters.c sorting_utils.c
OBJ         := $(SRC:.c=.o) $(FTPRINTF)
OBJ         := $(addprefix $(OBJDIR)/,$(OBJ))
LIBFT        = $(LIBFTDIR)/libft.a

INCL        := -I$(LIBFTDIR)

ASAN        ?= 1

NAME        := push_swap

ifneq ($(ASAN),0)
	CCFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CCFLAGS) $(INCL) -o $@ -c $<

$(OBJDIR):
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) bonus

clean:
	$(RM) $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
