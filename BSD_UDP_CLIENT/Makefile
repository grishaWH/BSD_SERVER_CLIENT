NAME = ../udp_client

FILES = Client.cpp  main.cpp  Package.cpp  Socket.cpp

INCLUDES = Client.h  includes.h  Package.h  profiler.h  Socket.h

INC_DIR = ./includes/

HEADERS = $(addprefix $(INC_DIR), $(INCLUDES))

deps = $(HEADERS) Makefile

SRC_DIR = ./srcs/

SRCS = $(addprefix $(SRC_DIR), $(FILES))

OBJ_DIR		= ./objs/
OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	g++ -std=c++17 $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(deps)
	mkdir -p $(OBJ_DIR)
	g++ -std=c++17 -MD -I $(INC_DIR) $< -c -o $@

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -rf $(NAME)

re:
	fclean all