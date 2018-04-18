# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 15:57:43 by dlinkin           #+#    #+#              #
#    Updated: 2018/01/15 15:57:45 by dlinkin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INC)
SRC =	gsh_core.c\
		gsh_env.c\
		gsh_env_process.c\
		gsh_env_process_2.c\
		gsh_graphics.c\
		gsh_help.c\
		gsh_init.c\
		gsh_interpreter.c\
		gsh_reader/gsh_reader.c\
		gsh_reader/gsh_reader_autocomplete.c\
		gsh_reader/gsh_reader_cut_copy_paste.c\
		gsh_reader/gsh_reader_esc.c\
		gsh_reader/gsh_reader_history.c\
		gsh_reader/gsh_reader_sym.c\
		gsh_reader/gsh_reader_tools.c\
		gsh_parcer/gsh_parcer.c\
		gsh_parcer/gsh_parcer_plus.c\
		gsh_parcer/gsh_parcer_plus_plus.c\
		gsh_pipes.c\
		gsh_parcer/gsh_pre_parcer.c\
		gsh_parcer/gsh_pre_pc_val.c\
		gsh_setenv.c\
		gsh_some_builtin1.c\
		gsh_some_redirections.c

OBJ = $(SRC:.c=.o)

OS = $(shell uname)
ifeq ($(OS),Darwin)
	INC = -I./libft/includes -I./includes
	LIBA = ./libft/libftprintf.a
	TCAP = -ltermcap
else
	INC = -I../../libft_win/includes -I./includes
	LIBA = ../../libft_win/libftprintf.a
	TCAP = -lcurses
endif

NAME = 21sh

CYAN = \x1b[1;36m
NON = \x1b[0m
STRING1 = $(CYAN)---Compile_21sh$(NON)
STRING2 = $(CYAN)---Remove_21sh_O_Files$(NON)
STRING3 = $(CYAN)---Remove_21sh$(NON)
STRING4 = $(CYAN)---Running$(NON)
STRING5 = $(CYAN)---Copy binary file in ~/my_bin$(NON)

.PHONY: $(LIBA)

all: $(LIBA) $(NAME)

$(NAME): $(OBJ)
	@echo "$(STRING1)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBA) $(TCAP) -o $(NAME)

$(LIBA):
ifeq ($(OS), Darwin)
	@make -C ./libft
else
	make -C ../../libft_win
endif

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean:
	@echo "$(STRING2)"
	@rm -rf $(OBJ)
ifeq ($(OS), Darwin)
	@make clean -C ./libft
else
	@make clean -C ../../libft_win
endif

fclean: clean
	@echo "$(STRING3)"
	@rm -rf $(NAME)
ifeq ($(OS), Darwin)
	@make clean_lib -C ./libft
else
	@make clean_lib -C ../../libft_win
endif

re: fclean all

run:
	@echo "$(STRING4)"
	@./21sh

test: ../tst.c
	@#$(CC) $(CFLAGS) ../main.c $(LIBA) -o ../tst
	@$(CC) $(CFLAGS) ../tst.c $(LIBA) $(TCAP) -o ../tst
	@../tst

os:
	@echo  "<"$(OS)"> OS it is"

inst:
	@echo "$(STRING5)"
	@cp $(NAME) ~/my_bin

dbg:
	./21sh 2>fil
