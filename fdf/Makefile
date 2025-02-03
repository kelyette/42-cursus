CC           := clang
RM           := rm -rf

CWFLAGS      := -Wall -Wextra -Werror
CCFLAGS      := $(CWFLAGS) -g

SRCDIR       := src
INCDIR       := include
OBJDIR       := target
LIBFTDIR     := libft
LIBMLXDIR    := minilibx

SRC           = main.c events.c events_mouse.c events_key.c events_utils.c \
				hmap.c hmap_utils.c hmap_parser.c \
				drawers.c draw_primitives.c draw_gui.c clr_utils.c \
				rotation.c vec3_utils.c vec3_projection.c actions.c
OBJ          := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
OBJ          += $(LIBFTDIR)/libft.a
SRC          := $(addprefix $(SRCDIR)/,$(SRC))

NAME         := fdf

LIBFLAGS     := -L$(LIBMLXDIR) -lm
INCFLAGS     := -I$(LIBMLXDIR) -I$(LIBFTDIR) -I$(INCDIR)

UNAME        := $(shell uname)

ifeq ($(UNAME),Linux)
	LIBFLAGS += -lmlx -lX11
else ifeq ($(UNAME),Darwin)
	LIBFLAGS += -lmlx -framework OpenGL -framework AppKit
endif

ASAN ?= 1 # TODO

ifneq ($(ASAN),0)
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

re: fclean all

as:
	$(MAKE) ASAN=1

.PHONY: all clean fclean re
