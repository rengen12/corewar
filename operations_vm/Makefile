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

.PHONY:		all clean

CFLAGS =	-Wall -Wextra -Werror -O2
SRC =		handle_add_sub.c handle_aff.c handle_forks.c handle_live.c \
			handle_lds.c handle_st.c handle_add_sub.c handle_and_or_xor.c \
			handle_zjmp.c  handle_ldis.c  handle_sti.c helpers.c

OBJFOLD =	obj/

HEADER =	-I ../

OBJ =		$(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(wildcard $(SRC))))

all:	$(OBJ)

$(OBJFOLD)%.o:	%.c
	@mkdir -p $(OBJFOLD)
	gcc $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@rm -rf $(OBJFOLD)
