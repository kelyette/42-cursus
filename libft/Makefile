CC = cc
AR = ar

CCFLAGS = -Wall -Wextra -Werror
ARFLAGS = rcs

INCL = libft.h
SRC := chrop integer io ischr lst_iter lst_manage lst_simple mem_copy mem_set mem_simple str_copy str_edit str_index str_simple
SRC := $(foreach src,$(SRC),ft_$(src).c)
OBJDIR = target
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

LIB = libft.a

INSTALLDIR = ~/libs

all: $(LIB)

install: $(LIB)
	@echo "installing to" $(INSTALLDIR)
	@mkdir -p $(INSTALLDIR)
	cp $< $(INSTALLDIR)/$<
	cp $(INCL) $(INSTALLDIR)/$(INCL)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)

$(OBJDIR)/%.o: %.c $(INCL)
	@mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@ -I.

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
