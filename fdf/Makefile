CC           := cc
RM           := rm -rf

CWFLAGS      := -Wall -Wextra -Werror
CCFLAGS      := $(CWFLAGS) -g -O3

SRCDIR       := src
INCDIR       := include
OBJDIR       := target
LIBFTDIR     := libft
LIBMLXDIR    := minilibx

SRC           = main.c events.c events_mouse.c events_key.c events_utils.c \
				str_utils.c info.c hmap.c hmap_utils.c hmap_parser.c \
				drawers.c draw_primitives.c clr_utils.c \
				rotation.c vec3_utils.c actions.c
OBJ          := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
OBJ          += $(LIBFTDIR)/libft.a $(LIBMLXDIR)/libmlx.a
SRC          := $(addprefix $(SRCDIR)/,$(SRC))

NAME         := fdf

ASAN         ?= 0
LIBFLAGS     := -L$(LIBMLXDIR) -lm
INCFLAGS     := -I$(LIBMLXDIR) -I$(LIBFTDIR) -I$(INCDIR)

UNAME        := $(shell uname)

ifeq ($(UNAME),Linux)
	LIBFLAGS := -lm -lmlx -lX11 -lXext -L$(LIBMLXDIR) -L/usr/lib/X11
else ifeq ($(UNAME),Darwin)
	LIBFLAGS += -lmlx -framework OpenGL -framework AppKit
	CCFLAGS += -D'COCOA'
endif

ifneq ($(ASAN),0)
	CCFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -o $@ -c $< $(INCFLAGS)

$(OBJDIR):
	mkdir -p $@

$(LIBFTDIR)/libft.a:
	$(MAKE) -C $(dir $@) bonus

$(LIBMLXDIR)/libmlx.a:
	$(MAKE) -C $(dir $@)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(LIBMLXDIR) clean

re: fclean all

as:
	$(MAKE) ASAN=1

.PHONY: all clean fclean re as
