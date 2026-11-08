NAME = malloc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIB_NAME = libft_malloc_$(HOSTTYPE).so
GCC = gcc
GCC_FLAGS = -Wall -Wextra -Werror

SRCS = ./src/malloc.c ./src/free.c ./src/realloc.c ./src/util.c
OBJS = ./src/malloc.o ./src/free.o ./src/realloc.o ./src/util.o

all: $(OBJS)
	@echo "                                     "
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "# - - - - - - - A L L - - - - - - - #"
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "                                     "

	$(GCC) $(GCC_FLAGS) -shared $(OBJS) -o $(LIB_NAME)
	$(GCC) $(GCC_FLAGS) main.c -o $(NAME)
	
	

clean:
	@echo "                                     "
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "# - - - - - - C L E A N - - - - - - #"
	@echo "# - - - - - - - - - - - - - - - - - #"
	@echo "                                     "
	@echo "rm -f $(NAME) $(LIB_NAME)"
	@rm -f $(NAME) $(LIB_NAME)
	@echo "rm -f $(OBJS)"
	@rm -f $(OBJS)

re: clean all
