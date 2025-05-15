MAKEFLAGS += --no-print-directory

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
HEADER = libft.h

BUILD_PATH = build

SRCS = \
ft_atoi.c \
ft_atoi_safe.c \
ft_bzero.c \
ft_calloc.c \
ft_count_tab.c \
ft_free_array.c \
ft_isspace.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_printf/ft_printf.c \
ft_printf/printf_itoa_unsigned.c \
ft_printf/printf_itoa.c \
ft_printf/printf_put_ptr.c \
ft_printf/printf_utils.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_puterror.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnprefix.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line.c \
get_next_line_utils.c \
w_calloc.c \
w_free.c \
w_kill.c \
w_malloc.c

OBJS = $(SRCS:%.c=$(BUILD_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Archiving $(NAME)...\n"
	@ar rc $(NAME) $(OBJS)
	@echo "Successfully COMPILED $(NAME)\n"

$(BUILD_PATH)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
