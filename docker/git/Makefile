EXO		= $(shell echo $${EXO})

CC		= gcc
CFLAGS		= -Wall -Werror -Wextra -I$(INCDIR) -I$(INCDIR)$(EXO)/ -DEXO=\"$(EXO)\"
LDFLAGS		= 

EXEC		= git
SRC		= $(SRC_NAMES:%=$(SRCDIR)%.c)
OBJ		= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

SRCDIR		= src/
OBJDIR		= obj/
INCDIR		= include/

SRC_NAMES	= main

all: $(EXEC)
.PHONY: all

clean:
	rm -rf $(OBJDIR)
	rm -f $(EXEC)
.PHONY: clean

re: clean all
.PHONY: re

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(dir $(OBJDIR)%.o)
	$(CC) $(CFLAGS) -o $@ -c $<

%/:
	mkdir -p $@
.PRECIOUS: %/
