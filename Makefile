# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/02 19:25:31 by alamorth          #+#    #+#              #
#    Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc

RM				= rm -f

CFLAGS			= -g -O3 -Wall -Wextra -Werror -I.

LIBFT			= libft/libft.a

LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

MLX				= mlx/libmlx.dylib

SRCS			= srcs/main.c srcs/parse.c srcs/key.c srcs/raycast.c \
				srcs/utils.c srcs/parse_utils.c srcs/move.c srcs/draw.c \
				srcs/free.c srcs/bmp.c srcs/sprite.c srcs/sprite_utils.c

OBJS			= $(SRCS:.c=.o)

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re