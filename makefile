# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timmi <timmi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 11:40:12 by timmi             #+#    #+#              #
#    Updated: 2025/04/04 14:40:11 by timmi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

BUILD_PATH = build

LIBFT_PATH = lib/libft
LIBFT = $(LIBFT_PATH)/libft.a

CFILES_PATH = src
CFILES =	$(CFILES_PATH)/main.c\
			$(CFILES_PATH)/prompt.c\

OBJ = $(CFILES:$(CFILES_PATH)/%.c=$(BUILD_PATH)/%.o)

NAME = minishell

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(BUILD_PATH)/%.o: $(CFILES_PATH)/%.c
	@mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	rm -f $(BUILD_PATH)/*.o
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(BUILD_PATH)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re