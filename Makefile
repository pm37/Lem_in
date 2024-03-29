# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:04:21 by bwan-nan          #+#    #+#              #
#    Updated: 2019/07/02 16:45:55 by pimichau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libftdb.a

# Reset
NC=\033[0m

# Regular Colors
BLACK=\033[0;30m
RED=\033[0;31m
GREEN =\033[32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m

CC = Clang
COMPILE = $(CC) -c
DEBUG = $(CC) -g

MKDIR = mkdir -p
CLEANUP = rm -rf

WFLAGS += -Wall
WFLAGS += -Werror
WFLAGS += -Wextra
DFLAGS = -fsanitize=address
IFLAGS = -I $(IPATH) -I $(LIPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)

OPATH = obj/
SPATH = src/
IPATH = inc/
TPATH = tools/
LPATH = libft/
LIPATH = libft/inc/

INCS += lem_in.h

SRC += ret_freetab.c
SRC += print_and_free.c
SRC += print_paths.c
SRC += print_input.c
SRC += del_functions.c

SRC += is_a_comment.c

SRC += lem_in.c
SRC += get_input.c
SRC += add_tunnels.c
SRC += init_anthill.c
SRC += add_rooms.c
SRC += find_paths.c
SRC += init_paths.c
SRC += init_ants.c
SRC += add_ants.c
SRC += update_queue.c
SRC += deviation.c
SRC += complete_paths.c
SRC += update_tunnels.c
SRC += test_solution.c
SRC += print_solution.c
SRC += start_linked_to_end.c


DSYM = $(NAME).dSYM

OBJ = $(patsubst %.c, $(OPATH)%.o, $(SRC))

vpath	%.c src/
vpath	%.c src/tools/
vpath	%.c src/add/
vpath	%.c src/display/
vpath	%.c src/init/
vpath	%.c src/algo/
vpath	%.h inc/
vpath	%.h libft/inc/

all : $(LIB) $(NAME)

debug : $(LIBDB) $(SRC)
	$(MAKE) -C $(LPATH) debug
	$(DEBUG) $(DFLAGS) $(CFLAGS) -o $(NAME) $^

$(NAME): $(LIB) $(OPATH) $(OBJ) $(INCS)
	$(CC) -o $@ $< $(OBJ)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJ) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $< -o $@
	printf "$(CYAN)Compiling $<\n$(NC)"

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

$(LIBDB) :
	$(MAKE) -C $(LPATH) debug

$(OPATH):
	$(MKDIR) $@

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJ)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYM)
	printf "$(RED)All objects removed from Lem_in\n$(NC)"

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)
	printf "$(RED)$(NAME) deleted\n$(NC)"

re: fclean all

.PHONY: all clean fclean debug
FORCE:
.SILENT:
