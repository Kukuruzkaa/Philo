# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/23 12:55:59 by ddiakova          #+#    #+#              #
#    Updated: 2022/01/19 19:53:25 by ddiakova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS 			= philo.c \
				philo_utils.c \
				args.c \
				init.c \
				routine.c \
				lib.c \
				lib2.c \
				output.c \
				join_free.c
				
OBJS			= $(SRCS:%.c=%.o)

RM 				= rm -rf

CC 				= clang
CFLAGS 			= -Wall -Werror -Wextra -g -pthread 
# FSAN			= -g3 -fsanitize=thread
SRCDIR 			= src
OBJDIR 			= objs

OBJS = $(addprefix ${OBJDIR}/,${SRCS:.c=.o})

all:			$(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} ${FSAN} -I./inc -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) ${FSAN} -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJDIR)
				
fclean:			clean
				$(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re bonus
