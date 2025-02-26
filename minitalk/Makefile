CC           := cc
RM           := rm -rf

CCFLAGS      := -Wall -Wextra -Werror -g

OBJDIR       := target
LIBFTDIR     := libft

SRV_SRC      := server.c
CLI_SRC      := client.c
LIBFT        := $(LIBFTDIR)/libft.a

SRV_OBJ      := $(addprefix $(OBJDIR)/,$(SRV_SRC:.c=.o))
CLI_OBJ      := $(addprefix $(OBJDIR)/,$(CLI_SRC:.c=.o))

ASAN         ?= 0

SNAME        := server
CNAME        := client

ifneq ($(ASAN),0)
	CCFLAGS += -fsanitize=address
endif

all: $(SNAME) $(CNAME)

$(SNAME): $(SRV_OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) -o $@ $^

$(CNAME): $(CLI_OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -I$(LIBFTDIR) -o $@ -c $<

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) bonus

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(SNAME) $(CNAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
