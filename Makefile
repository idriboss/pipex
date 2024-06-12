NAME = pipex

CC = cc

FLAGS = -Wall -Werror -Wextra

FILES = pipex.c	\

OBJ_DIR = objs/

OBJS = $(FILES:.c=.o)

OBJS_PREFIXD = (addprefix $(OBJ_DIR), $(OBJS))

libft = libft.a

LIBS = pipex.h

$(OBJ_DIR)%o : %c $(LIBS)
	@mkdir -p $(OBJ_DIR)
	@echo "compiling $<"
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJECTS_PREFIXED)
	@ar r $(NAME)