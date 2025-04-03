# **************************************************************************** #
#                                DIRECTORIES                                   #
# **************************************************************************** #
HEADER	=	minitalk.h

SRCS_CLIENT	=	mt_client.c \
				mt_utils.c

SRCS_SERVER	=	mt_server.c \
				mt_utils.c

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)

# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #
NAME_CLIENT	=	client
NAME_SERVER	=	server

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT)
	@echo "Successfully COMPILED $(NAME_CLIENT)"

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME_SERVER)
	@echo "Successfully COMPILED $(NAME_SERVER)"

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) -I. -I$(LIBFT_DIR) $< -o $@

clean:
	rm -rf $(OBJS_CLIENT) $(OBJS_SERVER)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
