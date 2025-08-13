# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/07/18 23:08:43 by oligrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name **************************************************************** #
NAME = philo

# Directories ***************************************************************** #
SRCS_DIR     = ./src
OBJS_DIR     = ./obj
INCLUDES_DIR = ./includes

# Subdirectories of src/ ***************************************************** #
EXT_DIR =		ext

# Source Files *************************************************************** #
SRCS_FILES =	main.c \
				init.c \
				cleanup.c \
				philo.c \
				$(EXT_DIR)/ft_atoi.c \
				$(EXT_DIR)/ft_isdigit.c \
				$(EXT_DIR)/ft_putstr.c \
				$(EXT_DIR)/ft_strlen.c 


# Full paths to source and object files ************************************** #
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# External libraries ********************************************************* #
LIBFT = $(LIBFT_DIR)/libft.a

# Compiler and flags ********************************************************* #
CC     = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR)

# Default rule *************************************************************** #
all: $(NAME)

# Build executable *********************************************************** #
$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Build complete."

# Compile .c to .o with directory creation *********************************** #
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and libraries ******************************************* #
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJS_DIR)
	@echo "Clean done."

# Clean everything *********************************************************** #
fclean: clean
	@rm -f $(NAME)

# Rebuild ******************************************************************** #
re: fclean all

# Phony targets ************************************************************** #
.PHONY: all clean fclean re
