ExecName= game
OUT = -o $(ExecName)
SRCS= shapes.cpp
LIBS= -lraylib -lglfw -lGL -lopenal -lm -pthread -ldl -lstdc++
ARGS = -w -std=c++11 -I. -L. $(LIBS) $(SRCS) $(OUT)
CC = c++
default:make


make:
	$(CC) $< $(ARGS)
	./$(ExecName)
.PHONY: clean

clean:
	rm -r $(OBJ) $(ExecName)