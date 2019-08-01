# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 13:33:28 by amansour          #+#    #+#              #
#    Updated: 2019/07/02 09:55:59 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

################################################################################
# SOURCES       															   #
################################################################################

SRCS		= $(addprefix $(PATH_SRC)/, \
							address.c\
							display_blocks.c\
							blocks.c\
							calloc.c\
							char.c\
							free.c\
							hexdump.c\
							realloc.c\
							malloc.c\
							number.c\
							show_alloc_mem.c\
							size.c\
							string.c\
							tools.c\
							zones.c)

################################################################################
# BASIC VARIABLES															   #
################################################################################

PATH_OBJ	= obj
PATH_SRC	= srcs
PATH_INC	= includes

NAME		= libft_malloc_$(HOSTTYPE).so
CFLAGS		= -Wall -Wextra -Werror
DLFLAGS		= -shared -fPIC
OBJECTS 	= $(SRCS:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)

################################################################################
# RULES																		   #
################################################################################

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(DLFLAGS) -o $@ $(OBJECTS)
	@rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so
	@echo $(GREEN) "[√]     [libft_malloc.so  Successfully Compiled!]" $(WHITE)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	@$(CC) -c -o $@ $(CFLAGS) $^ -I $(PATH_INC)/

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(PATH_OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f libft_malloc.so

re: fclean $(NAME)

# Text Colorization------------------------------------------------------------
GREEN = "\033[1;32m"
WHITE = "\033[´0m"
.PHONY: all clean fclean re
