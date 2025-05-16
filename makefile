# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timmi <timmi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/05/16 13:07:53 by timmi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MAKEFLAGS += --no-print-directory

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra

BUILD_PATH = build

LIBFT_PATH = lib/libft
LIBFT = $(LIBFT_PATH)/libft.a

CFILES_PATH = src
CFILES =	$(CFILES_PATH)/main.c\
			$(CFILES_PATH)/lexer/lexer_utils.c\
			$(CFILES_PATH)/lexer/lexer.c\
			$(CFILES_PATH)/parser/parser_add_node.c\
			$(CFILES_PATH)/parser/parser_func.c\
			$(CFILES_PATH)/parser/parser_utils.c\
			$(CFILES_PATH)/parser/parser_main.c\
			$(CFILES_PATH)/parser/syntax_analysis.c\
			$(CFILES_PATH)/prompt/prompt.c\
			$(CFILES_PATH)/utils/exit_utils.c\
			$(CFILES_PATH)/utils/free_ast.c\
			$(CFILES_PATH)/utils/list.c\
			$(CFILES_PATH)/utils/env_utils.c\
			$(CFILES_PATH)/exec/exec.c\
			$(CFILES_PATH)/exec/pipe.c\
			$(CFILES_PATH)/builtin/ft_echo.c\
			$(CFILES_PATH)/builtin/ft_cd.c\
			$(CFILES_PATH)/builtin/ft_pwd.c\
			$(CFILES_PATH)/builtin/ft_env.c\
			$(CFILES_PATH)/builtin/ft_unset.c\
			$(CFILES_PATH)/builtin/ft_export.c\
			$(CFILES_PATH)/init/init_env.c\
			$(CFILES_PATH)/init/init_shell.c\

OBJ = $(CFILES:$(CFILES_PATH)/%.c=$(BUILD_PATH)/%.o)

NAME = minishell

all:
	@echo "Building $(NAME)...\n"
	@$(MAKE) $(LIBFT)
	@$(MAKE) $(NAME)
	@echo "Done."

$(LIBFT):
	@echo "Building libft...\n"
	@$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking $(NAME)...\n"
	@$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(BUILD_PATH)/%.o: $(CFILES_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=resources/a.supp --log-file="resources/leaks.log" ./minishell

clean:
	@echo "Cleaning object files...\n"
	@rm -f $(BUILD_PATH)/*.o
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@echo "Fully cleaning project...\n"
	@rm -f $(NAME)
	@rm -rf $(BUILD_PATH)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
