CC           := cc
RM           := rm -rf

CCFLAGS      := -Wall -Wextra -Werror -g
ASAN         ?= 1 # TODO

SRCDIR       := src
INCDIR       := include
OBJDIR       := target

SRC          := philosophers.c
OBJ          := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

NAME         := philo

ifneq ($(ASAN),0)
	CCFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -I$(INCDIR) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean re

.PHONY: all clean fclean re
