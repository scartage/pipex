NAME		= pipex
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -MMD -g -fsanitize=address -fsanitize=undefined
RM			= rm -rf

INCLUDES	= inc/pipex.h

SRCS		= main.c file_handler.c command.c arguments.c args_state.c

SRC_DIRS	= src

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix  $(OBJ_DIR)/, $(SRCS:.c=.d))

LIBFT		= libft/libft.a

vpath %.c src $(addprefix  src/, $(SRC_DIRS))

green := $(shell tput setaf 2)
nc := $(shell tput sgr0)

$(OBJ_DIR)/%.o: %.c Makefile
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all: make_dir make_libs $(NAME)

make_libs:
	@$(MAKE) -s -C libft

make_dir:
		@mkdir -p $(OBJ_DIR)

-include $(DEPS)
$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
		@echo "$(green)$(NAME) compiled$(nc)"

clean:
	@$(MAKE) -C libft fclean
	$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all

test: all
	@$(MAKE) -C tests

.PHONY: all clean fclean re test