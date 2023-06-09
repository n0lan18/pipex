# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nleggeri <nleggeri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 11:10:16 by nleggeri          #+#    #+#              #
#    Updated: 2023/03/16 11:15:43 by nleggeri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=			pipex

SRC				=			src/main.c \
							src/pipex.c \

OBJS				=			$(SRC:.c=.o)

LIBFT				=			./libft/libft.a
MLIBFT				=			$(MAKE) -C ./libft

CC				=			gcc
CFLAGS				=			-Wall -Werror -Wextra -g
L				=			-fsanitize=address
RM				=			rm -f

all :	lib $(NAME)

lib :
			$(MLIBFT) all

%.o :	%.c ./libft/libft.h Makefile header.h
							$(CC) $(CFLAGS) -c $< -o $@

$(NAME) :	$(OBJS)
							${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

clean	:
							${RM} ${OBJS}

fclean	:	clean
							${RM} ${NAME}
							cd libft && make fclean

re	:	fclean all

.PHONY	:	all clean fclean
