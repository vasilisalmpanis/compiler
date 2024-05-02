CC 	= g++
NAME	= lexer
SRC	= src/main.cpp \
	  src/lexer.cpp \
	  src/parser.cpp \
	  src/syntax.cpp \
	  src/evaluator.cpp

INC	= -I/home/valmpani/Desktop/repo/comp/includes/
OBJS	= $(SRC:.cpp=.o)
CFLAGS  = -g -Wall -std=c++17 -fsanitize=address
# The build target 
all : $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(NAME) $(OBJS)

re: clean all

.PHONY: all clean re
