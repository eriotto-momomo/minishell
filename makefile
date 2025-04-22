# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 11:40:12 by timmi             #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/04/17 17:14:52 by timmi            ###   ########.fr        #
=======
#    Updated: 2025/04/19 18:42:37 by emonacho         ###   ########.fr        #
>>>>>>> main
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
<<<<<<< HEAD
			$(CFILES_PATH)/prompt.c\
			$(CFILES_PATH)/lexer.c\
			$(CFILES_PATH)/list.c\
			$(CFILES_PATH)/utils.c\
			$(CFILES_PATH)/parser.c\
=======
			$(CFILES_PATH)/lexer/lexer_utils.c\
			$(CFILES_PATH)/lexer/lexer.c\
			$(CFILES_PATH)/parser/parser_cmd.c\
			$(CFILES_PATH)/parser/parser_func.c\
			$(CFILES_PATH)/parser/parser_utils.c\
			$(CFILES_PATH)/parser/parser.c\
			$(CFILES_PATH)/prompt/prompt.c\
			$(CFILES_PATH)/utils/list.c\

>>>>>>> main

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
