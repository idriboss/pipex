#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#


SRCS = ft_memset.c        		\
        ft_bzero.c        		\
        ft_memcpy.c        		\
        ft_memmove.c     		\
        ft_memchr.c        		\
        ft_memcmp.c        		\
        ft_strlen.c        		\
        ft_isalpha.c     		\
        ft_isdigit.c        	        \
        ft_isalnum.c        	        \
        ft_isascii.c        	        \
        ft_isprint.c        	        \
        ft_toupper.c        	        \
        ft_tolower.c        	        \
        ft_strchr.c        		\
        ft_strrchr.c        	        \
        ft_strncmp.c        	        \
        ft_strlcpy.c        	        \
        ft_strlcat.c        	        \
        ft_strnstr.c        	        \
        ft_atoi.c        		\
        ft_calloc.c        		\
        ft_strdup.c        		\
        ft_striteri.c       	        \
        ft_substr.c        		\
        ft_strjoin.c     		\
        ft_strtrim.c        	        \
        ft_split.c        		\
        ft_itoa.c        		\
        ft_strmapi.c        	        \
        ft_putchar_fd.c   		\
        ft_putstr_fd.c    		\
        ft_putendl_fd.c    		\
        ft_putnbr_fd.c   		\
        get_next_line.c 		\
        get_next_line_utils.c           \
        ft_printf.c     		\
        ft_printf_utils.c               \
        ft_printf_converts.c            \
	ft_re_strjoin.c			\
	free_2d_array.c			\
	ft_re_strdup.c			\
	multi_strjoin.c			\
	multi_re_strjoin.c		\
	ft_strcmp.c			\
	ft_free.c			\
	ft_close_fd.c			\
	print_2d_array_nl.c		\
        ft_multi_free.c                 \

SRCSB =    ft_lstnew.c			\
        ft_lstadd_front.c		\
        ft_lstsize.c			\
        ft_lstlast.c			\
        ft_lstadd_back.c		\
        ft_lstclear.c			\
        ft_lstdelone.c			\
        ft_lstiter.c			\
        ft_lstmap.c			\
        $(SRCS)

NAME = libft.a
LIBS = libft.h ft_printf.h get_next_line.h
OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

OBJSB = $(SRCSB:.c=.o)
OBJECTS_BONUS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJSB))

CC = cc

CC_FLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c $(LIBS)
	@mkdir -p $(OBJS_DIR)
	@echo "$(YELLOW)Compiling: $<$(END)"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_PREFIXED)
	@echo "$(GREEN)Libft Done !$(END)"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BLUE)remove objects$(END)"

fclean: clean
	@echo "$(BLUE)remove $(NAME)$(END)"

re: fclean all

bonus: $(OBJECTS_BONUS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_BONUS_PREFIXED)
	@echo "$(GREEN)Libft Bonus Done !$(END)"
