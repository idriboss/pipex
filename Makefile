#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

NAME = pipex

CC = 	gcc


SRC_PATH = ./src/

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

LIBFT_FILES = $(wildcard $(LIBFT_PATH)/*c)		\

FLAGS = -Wall -Werror -Wextra -g3 -I$(SRC_PATH)

FILES = 	$(wildcard $(SRC_PATH)*.c)			\
			$(LIBFT_PATH)/libft.a				\

all : 	$(NAME)

$(LIBFT): $(LIBFT_FILES)
			@make all -C $(LIBFT_PATH)

$(NAME) : $(LIBFT) $(FILES)
			
			@$(CC) $(FLAGS) $(FILES) -o $(NAME)
			@printf "$(GREEN)$(NAME) done !$(END)"

bonus : $(NAME)

clean :
			@make clean -C $(LIBFT_PATH)

fclean :
			@make fclean -C $(LIBFT_PATH)
			@rm -rf $(NAME)
			@echo "$(BLUE)remove $(NAME)$(END)"

re : 	fclean all