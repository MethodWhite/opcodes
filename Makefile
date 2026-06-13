CC       := gcc
CFLAGS   := -flto -Wall -Wextra -Wno-unused-function -Wno-unused-variable \
            -Wno-sign-compare -Wno-format -march=native -O3
LDFLAGS  := -flto
EXE      := code.exe
TEST_EXE := tests/test_opcodes.exe

.PHONY: all clean test library

all: $(EXE)

$(EXE): code.c
	$(CC) $(CFLAGS) code.c -o $(EXE)

compile_debug: CFLAGS += -DDEBUG_ENABLE
compile_debug: all

test: tests/test_opcodes.c
	$(CC) $(CFLAGS) -I. -Itests tests/test_opcodes.c -o $(TEST_EXE)
	./$(TEST_EXE)

clean:
	rm -f $(EXE) $(TEST_EXE)
