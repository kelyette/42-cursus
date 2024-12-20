CC          := clang
RM          := rm -rf

CWFLAGS     := -Wall -Wextra -Werror
CCFLAGS     := $(CWFLAGS) -g

SRCDIR      := src
INCDIR      := include
OBJDIR      := target
LIBFTDIR    := libft
LIBMLXDIR   := minilibx

SRC          = main.c events.c events_mouse.c events_key.c events_utils.c \
			   hmap.c hmap_utils.c drawers.c rotation.c actions.c
OBJ         := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
OBJ         += $(LIBFTDIR)/libft.a
SRC         := $(addprefix $(SRCDIR)/,$(SRC))

NAME        := fdf

LIBFLAGS    := -L$(LIBMLXDIR) -lm
INCFLAGS    := -I$(LIBMLXDIR) -I$(LIBFTDIR) -I$(INCDIR)

UNAME       := $(shell uname)

ifeq ($(UNAME),Linux)
	LIBFLAGS += -lmlx -lX11
else ifeq ($(UNAME),Darwin)
	LIBFLAGS += -lmlx -framework OpenGL -framework AppKit
endif

ifdef ASAN
	CCFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(LIBFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) $(INCFLAGS) -o $@ -c $<

$(OBJDIR):
	mkdir -p $@

$(LIBFTDIR)/libft.a:
	$(MAKE) -C $(dir $@) bonus

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
