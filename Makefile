# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 13:33:28 by amansour          #+#    #+#              #
#    Updated: 2019/05/29 13:33:33 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

################################################################################
# BASIC VARIABLES															   #
################################################################################

PATH_OBJ	= obj
PATH_SRC	= src
PATH_INC	= inc

NAME		= libft_malloc_$(HOSTTYPE).so
CFLAGS		= -Wall -Wextra -Werror
DLFLAGS		= -shared -fPIC
OBJECTS		= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))
DEBUG		= -g -O0

################################################################################
# SOURCES       															   #
################################################################################

SRCS		= $(addprefix $(PATH_SRC)/, \
							free.c\
							malloc.c\
							calloc.c\
							realloc.c\
							size.c\
							blocks.c\
							tools.c\
							zones.c\
							show_alloc_mem.c)



################################################################################
# RULES																		   #
################################################################################

.PHONY: all

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(DLFLAGS) -o $@ $(OBJECTS)
	@rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so
	@echo libft_malloc.so now link to $(NAME)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g  -I $(PATH_INC)/

clean:
	@rm -f $(OBJECTS)
	@echo Delete $(words $(OBJECTS)) object file

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean $(NAME)