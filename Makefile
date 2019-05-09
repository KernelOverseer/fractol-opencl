# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <kerneloverseer@protonmail>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/15 20:38:11 by abiri             #+#    #+#              #
#    Updated: 2019/05/09 17:10:33 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_lCYAN = \x1b[96m
_lYELLOW = \x1b[93m
_lGREEN = \x1b[92m
_lBLUE = \x1b[94m
_RED = \x1b[31m
_BOLD = \x1b[1m
_END = \x1b[0m

NAME = fractol

SRC = src/main.c\
	  src/init.c\
	  src/events.c\
	  src/images.c\
	  src/colors.c\
	  src/fractals/ft_gpu_mandelbrot.c\
	  src/fractals/ft_gpu_julia.c\
	  src/fractals/ft_gpu_burningship.c\
	  src/fractals/ft_gpu_burningshipfifth.c\
	  src/fractals/ft_gpu_celticmandelbar.c\
	  src/opencltools.c

FLAGS = -Wall -Werror -Wextra -framework OpenGL -framework AppKit

INCLUDES = -I ./libs/libft\
		   -I ./libs/minilibx\
		   -I ./inc

LIBRARIES = -L ./libs/libft	-lft\
			-L ./libs/libft/ft_printf -lftprintf\
			-L ./libs/minilibx -lmlx\
			-framework OpenCL

DELAY = 0

all : $(NAME)
$(NAME):
	@echo "                                                    ";
	@echo "                                                    ";
	@echo "                                                    ";
	@echo "                                                    ";
	@echo "                                                    ";
	@echo "███████╗██████╗  █████╗  ██████╗████████╗ ██████╗ ██╗     ";
	@echo "██╔════╝██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██╔═══██╗██║     ";
	@echo "█████╗  ██████╔╝███████║██║        ██║   ██║   ██║██║     ";
	@echo "██╔══╝  ██╔══██╗██╔══██║██║        ██║   ██║   ██║██║     ";
	@echo "██║     ██║  ██║██║  ██║╚██████╗   ██║   ╚██████╔╝███████╗";
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚══════╝";
	@echo "                                                    ";
	@echo "                                                    ";
	@echo "                                                    ";
	@echo "                                                    ";
	@echo "                                                    ";
	@make -C ./libs/libft
	@echo "gcc $(_lYELLOW)$(FLAGS)$(_END) $(_lCYAN)$(SRC)$(_END)\n$(_lGREEN)$(LIBRARIES)$(_END) -I$(_RED)./inc$(_END)$(_RED)$(INCLUDES)$(_END) -o $(_lBLUE)$(NAME)$(_lEND)$(_RED)\n"
	@gcc $(FLAGS) $(SRC) $(LIBRARIES) $(INCLUDES) -o $(NAME)
clean:
	@echo "\n$(_lCYAN)Makefile :$(_END) will delete $(_RED)$(SRC:.c=.o)$(_END)"
	@echo "starting in $(DELAY) sec, $(_RED)press Ctrl-c to abort$(_END)"
	@sleep $(DELAY)
	@rm -f $(SRC:.c=.o)
fclean: clean
	@echo "\n$(_lCYAN)Makefile :$(_END) will delete $(_RED)$(NAME)$(_END)"
	@echo "starting in $(DELAY) sec, $(_RED)press Ctrl-c to abort$(_END)"
	@sleep $(DELAY)
	@rm -f $(NAME)
fast:
	@rm -f $(NAME)
	@rm -f $(SRC:.c=.o)
	@gcc $(FLAGS) $(SRC) $(LIBRARIES) -I./inc -I$(INCLUDES) -o $(NAME)
re: fclean all
