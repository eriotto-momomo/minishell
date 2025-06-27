# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/06/27 09:38:22 by emonacho         ###   ########.fr        #
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
			$(CFILES_PATH)/lexer/token_list.c\
			$(CFILES_PATH)/loop/main_loop.c \
			$(CFILES_PATH)/loop/prompt.c\
			$(CFILES_PATH)/parser/parser_add_node.c\
			$(CFILES_PATH)/parser/parser_func.c\
			$(CFILES_PATH)/parser/parser_utils.c\
			$(CFILES_PATH)/parser/parser_main.c\
			$(CFILES_PATH)/parser/syntax_analysis.c\
			$(CFILES_PATH)/utils/exit_utils.c\
			$(CFILES_PATH)/utils/free_ast.c\
			$(CFILES_PATH)/utils/general.c\
			$(CFILES_PATH)/utils/env_utils.c\
			$(CFILES_PATH)/utils/identifier.c\
			$(CFILES_PATH)/heredoc_redir/redir.c\
			$(CFILES_PATH)/heredoc_redir/heredoc_write.c\
			$(CFILES_PATH)/heredoc_redir/heredoc_utils.c\
			$(CFILES_PATH)/heredoc_redir/heredoc_create.c\
			$(CFILES_PATH)/exec/exec.c\
			$(CFILES_PATH)/exec/exec_utils.c\
			$(CFILES_PATH)/exec/pathfinder.c\
			$(CFILES_PATH)/exec/signals.c\
			$(CFILES_PATH)/errors/print_error.c\
			$(CFILES_PATH)/builtin/ft_echo.c\
			$(CFILES_PATH)/builtin/ft_cd.c\
			$(CFILES_PATH)/builtin/ft_pwd.c\
			$(CFILES_PATH)/builtin/ft_env.c\
			$(CFILES_PATH)/builtin/ft_unset.c\
			$(CFILES_PATH)/builtin/ft_export.c\
			$(CFILES_PATH)/builtin/ft_exit.c\
			$(CFILES_PATH)/init/init_env.c\
			$(CFILES_PATH)/init/init_shell.c\
			$(CFILES_PATH)/expand/word_processing.c\
			$(CFILES_PATH)/expand/var_expansion.c\
			$(CFILES_PATH)/expand/var_expansion_utils.c\

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
