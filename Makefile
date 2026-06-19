CC       = gcc
CFLAGS   = -Wall -Wextra -I include -g -std=gnu99
SRC_DIR  = src
OBJ_DIR  = obj
TARGET   = petshop

ifeq ($(OS),Windows_NT)
EXE = .exe
else
EXE =
endif

SRCS     = main.c $(wildcard $(SRC_DIR)/*.c)
OBJS     = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

.PHONY: all clean run

all: $(OBJ_DIR) $(TARGET)$(EXE)

$(OBJ_DIR):
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c include/servico.h include/consulta.h include/util.h

$(OBJ_DIR)/servico.o: $(SRC_DIR)/servico.c include/servico.h include/util.h

$(OBJ_DIR)/consulta.o: $(SRC_DIR)/consulta.c include/consulta.h include/util.h

$(TARGET)$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET)$(EXE)
	$(TARGET)$(EXE)

clean:
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	@if exist "$(TARGET)$(EXE)" del "$(TARGET)$(EXE)"
