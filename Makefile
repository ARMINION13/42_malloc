NAME = malloc
GCC = gcc
GCC_FLAGS = -Wall -Wextra -Werror

SRCS = ./src/malloc.c ./src/free.c ./src/realloc.c
OBJS = ./src/malloc.o ./src/free.o ./src/realloc.o

all: $(OBJS)
	@echo "                                     "
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "# - - - - - - - A L L - - - - - - - #"
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "                                     "

	$(GCC) $(GCC_FLAGS) $(OBJS) main.c -o $(NAME)
	

clean:
	@echo "                                     "
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "# - - - - - - C L E A N - - - - - - #"
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "                                     "
	@echo "rm -f $(LIB_NAME)"
	@rm -f $(LIB_NAME)
	@echo "rm -f $(NAME)"
	@rm -f $(NAME)
	@echo "rm -f $(OBJS)"
	@rm -f $(OBJS)

re: clean all
