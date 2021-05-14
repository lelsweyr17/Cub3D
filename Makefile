# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/07 15:44:51 by lelsweyr          #+#    #+#              #
#    Updated: 2021/02/08 18:30:30 by lelsweyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
COMP = gcc -Wall -Wextra -Werror
INCL = parcer.h get_next_line.h
C_FILES = main.c parcer.c parcer2.c map_init.c map_init_2.c validator.c textures.c \
	sprites.c sprites_2.c draw_3d.c floor_ceilling.c get_next_line_utils.c get_next_line.c \
	key_flags.c screenshot.c \
	libft/ft_lstadd_back.c libft/ft_lstnew.c libft/ft_lstsize.c \
	libft/ft_lstdelone.c libft/ft_lstlast.c libft/ft_lstclear.c libft/ft_calloc.c \
	libft/ft_bzero.c libft/ft_strncmp.c
O_FILES = $(C_FILES:.c=.o)
MLX = minilibx_opengl/libmlx.a
LIB = libft/libft.a
MLX_FLAGS = -framework OpenGL -framework Appkit

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(O_FILES)
	@echo "\nCompiling...\n"
	@$(MAKE) -C minilibx_opengl
	$(COMP) -o $(NAME) $(MLX) $(MLX_FLAGS) $(O_FILES)

clean:
	@echo "\nCleaning...\n"
	@$(MAKE) -C libft clean
	rm -rf $(O_FILES)

fclean: clean
	rm -rf *.bmp
	@$(MAKE) -C minilibx_opengl clean
	rm -rf $(NAME)
	
re: fclean all