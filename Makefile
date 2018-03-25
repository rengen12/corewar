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

CORDIR = vm/

ASMDIR = asm_dir/

SERVERDIR = net/Serv

CLIENTDIR = net/Client

all:
	@make -C $(CORDIR)
	@make -C $(ASMDIR)
	@make -C $(SERVERDIR)
	@make -C $(CLIENTDIR)
	@mv ./$(CORDIR)/corewar ./
	@mv ./$(ASMDIR)/asm ./
	@mv ./$(ASMDIR)/dasm ./
	@mv ./$(SERVERDIR)/server ./
	@mv ./$(CLIENTDIR)/client ./
	@tar -xf resources.tar

clean:
	@make clean -C $(CORDIR)
	@make clean -C $(ASMDIR)
	@make clean -C $(SERVERDIR)
	@make clean -C $(CLIENTDIR)

fclean: clean
	rm -rf  corewar asm server client dasm resources

re: fclean all
