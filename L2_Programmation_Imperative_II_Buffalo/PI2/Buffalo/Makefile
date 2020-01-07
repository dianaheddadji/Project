CC = gcc
CFLAGS = -Wall -O3

SRC = display.c indianMovement.c dogsMovement.c gameplay.c gameover.c IaBuffalo4Indian.c IaBuffalo4dogs.c IaBuffalo4closer.c iadogs.c main.c
OBJ = $(subst .c,.o,$(SRC))
BIN = buffalo
DEP = _dependencies.mk

all:: $(DEP) $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

%.o:	%.c
	$(CC) -c $< $(CFLAGS)


$(DEP): $(SRC)
	$(CC) -MM $^ > $@

clean::
	rm -f $(BIN) $(OBJ) $(DEP) *~

-include $(DEP)
