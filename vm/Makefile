# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amichak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 11:53:43 by amichak           #+#    #+#              #
#    Updated: 2018/01/23 12:07:30 by amichak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:		all clean fclean re $(NAME)

CFLAGS =	-Wall -Wextra -Werror -O2
SRC =		main.c handle_error.c handle_player.c handle_players.c \
			handle_process.c helpers.c parse_flags.c pr_memory.c visual1.c \
			prerr_fr.c start_game.c find_winner.c helpers_player.c \
			helpers_process.c visual.c set_waiting.c handle_events.c

NAME =		corewar
OBJFOLD =	obj/
LIBFT =		./libft/
LIB =		-L. libft/libft.a
OPER =		operations_vm/
OPEROBJ =	operations_vm/obj/*.o
HEADER =	-I ./

OBJ =		$(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRC)))

all:		$(NAME)

$(NAME):	libs $(OBJ)
	gcc $(CFLAGS) $(HEADER) -o $(NAME) $(OBJ) $(OPEROBJ) $(LIB) -lncurses
	@echo "corewar: done"

libs:
	@make -C $(LIBFT) -f Makefile
	@make -C $(OPER) -f Makefile

$(OBJFOLD)%.o:	%.c
	@mkdir -p $(OBJFOLD)
	gcc $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make -C $(LIBFT) -f Makefile clean
	@make -C $(OPER) -f Makefile clean
	@rm -rf $(OBJFOLD)

fclean:		clean
	@make -C $(LIBFT) -f Makefile fclean
	@rm -f $(NAME)

re:			fclean all
