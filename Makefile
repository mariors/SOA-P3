CC = gcc
MK_DIR = mkdir
HEADERS = -Iheaders/
LIBS_FOLDER_FLAG = -Llib/
LIBS_FLAG = 

C_FLAGS = -Wall -lm -Os -lrt $(HEADERS) \
	$(LIBS_FOLDER_FLAG) \
	$(LIBS_FLAG)

SRC_DIR = src
BIN_DIR = bin

MAIN_FILE = project.o

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(BIN_DIR)/$(MAIN_FILE)

build: compile
	@echo DONE!
	@echo Compilation done.
	@echo and then run with: ./$(OBJ)

compile: clean
	@echo COMPILING...
	$(CC) $(SRC) $(C_FLAGS) -o $(OBJ)

clean:
	@echo CLEANING STEP!
	$(RM) -rf $(BIN_DIR)/*.o $(BIN_DIR)
	$(MK_DIR) $(BIN_DIR)