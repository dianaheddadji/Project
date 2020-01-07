CC = gcc
CFLAGS = -std=c99 -c
LDFLAGS =

SRC = main.c display.c game.c
OBJ = $(subst .c,.o,$(SRC))
BIN = puissance6
DEP = _dependencies.mk

all:: $(DEP) $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

$(OBJ):
	$(CC) $(CFLAGS) $< -o $@

$(DEP): $(SRC)
	$(CC) -MM $^ > $@

clean::
	rm -f $(BIN) $(OBJ) $(DEP) *~

-include $(DEP)
