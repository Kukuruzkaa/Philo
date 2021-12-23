# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/23 12:55:59 by ddiakova          #+#    #+#              #
#    Updated: 2021/12/23 17:59:25 by ddiakova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

LIBFT 			= Libft/libft.a

SRCS 			= philo.c
				
OBJS			= $(SRCS:%.c=%.o)

RM 				= rm -rf

CC 				= clang
CFLAGS 			= -Wall -Werror -Wextra -g -c 
#FSAN			= -g3 -fsanitize=address
SRCDIR 			= src
OBJDIR 			= objs

OBJS = $(addprefix ${OBJDIR}/,${SRCS:.c=.o})

all:			$(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} ${FSAN} -I./inc -c $< -o $@

$(LIBFT):
				@make bonus -C Libft

$(NAME):		$(OBJS) $(LIBFT)
				$(CC) ${FSAN} -o $(NAME) $(OBJS) $(LIBS) Libft/libft.a

clean:
				$(RM) $(OBJDIR)
				make clean -C Libft
				
fclean:			clean
				$(RM) $(NAME)
				make fclean -C Libft

re: 			fclean all

.PHONY: 		all clean fclean re bonus
