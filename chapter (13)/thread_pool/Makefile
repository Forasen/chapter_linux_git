EXE_DIR :=./bin
INC_DIR :=./include
SRC_DIR :=./src

OBJECTS := ./src/pool_main.c ./src/pool_thread.c ./src/pool_que.c

INCLUDES := ./include/pool_que.h ./include/pool_thread.h ./include/pool_common.h

$(EXE_DIR)/main: $(OBJECTS) $(INCLUDES)
	gcc -g  -o $@ $(OBJECTS) -I$(INC_DIR) -lpthread
