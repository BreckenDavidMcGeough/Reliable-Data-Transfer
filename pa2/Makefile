INC_DIR	= ./include
SRC_DIR = ./src
OBJ_DIR	= ./object

BINS = abt gbn sr

LIBS = 
CC	= gcc
CFLAGS	= -g -I$(INC_DIR) -std=c99

all: $(BINS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINS): %: $(OBJ_DIR)/simulator.o $(OBJ_DIR)/%.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJ_DIR)/*.o $(INC_DIR)/*~ $(BINS)
