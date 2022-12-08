# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 14:57:52 by iakry             #+#    #+#              #
#    Updated: 2022/12/07 23:59:02 by mbelbiad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRCS	= main.c init.c utils.c utils2.c castrays.c castraysutils.c render.c 3dprojection.c

OBJS	= $(SRCS:.c=.o)

FLAGS	= -lmlx -framework OpenGL -framework AppKit -g  -Wall -Wextra -Werror


all:			$(NAME)

$(NAME):		$(SRCS)
				gcc $(FLAGS) $(SRCS) -fsanitize=address -o $(NAME)

clean:
				rm -rf $(OBJS)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

run:			re
				./cub3d