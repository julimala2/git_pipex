SHELL := bash
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

PRINTF_DIR = ft_printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

ORANGE = $(shell tput setaf 202)
RED = $(shell tput setaf 1)
YELLOW = $(shell tput setaf 3)
BLUE = $(shell tput setaf 27)
GREEN = $(shell tput setaf 46)
RESET = $(shell tput sgr0)

.SILENT:

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(PRINTF_LIB) $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(PRINTF_LIB) -o $(NAME)
	@echo -e "$(GREEN)Compiling OKKKKKKKKK ehehhehehehehe$(RESET)"

$(LIBFT_LIB):
	@echo -e "$(ORANGE)Compiling Libft...$(RESET)"
	$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	
$(PRINTF_LIB):
	@echo -e "$(ORANGE)Compiling Printf...$(RESET)"
	$(MAKE) --no-print-directory -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -f $(OBJ)
	$(MAKE) --no-print-directory -C $(PRINTF_DIR) clean
	$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) --no-print-directory -C $(PRINTF_DIR) fclean
	$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
