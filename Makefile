# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/13 20:30:34 by vtenigin          #+#    #+#              #
#    Updated: 2017/01/17 17:47:59 by vtenigin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FILES = main.c readroom.c readlink.c

OBJECTS = $(FILES:.c=.o)

CFLAG = -Wall -Werror -Wextra -g

ATTACH = -L libft/ -lft

all: $(NAME)

$(NAME):
	# make -C libft/
	gcc $(CFLAG) -o $(NAME) $(FILES) $(ATTACH)

clean:
	/bin/rm -f $(OBJECTS)
	# make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	# make -C libft/ fclean

re: fclean all