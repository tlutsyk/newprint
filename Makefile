#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/01 18:57:51 by tlutsyk           #+#    #+#              #
#    Updated: 2018/01/01 18:57:51 by tlutsyk          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SWITCH =		\033[
STYLE_NORMAL =	$(SWITCH)0m
COLOR_GREEN = 	$(SWITCH)42m
COLOR_RED =		$(SWITCH)41m

NAME = libftprintf.a
O_FILES =  objects/*.o

all: $(NAME)

$(NAME): objectdir
	@make -C ft_printf
	@make -C libft
	@ar rc $(NAME) $(O_FILES)
	@echo "$(STYLE_BOLD)$(COLOR_GREEN) libftprintf has been compiled.$(STYLE_NORMAL)"

objectdir:
	@mkdir -p objects

clean:
	@make clean -C libft
	@make clean -C ft_printf
	@rm -rf objects
	@echo "$(STYLE_BOLD)$(COLOR_RED)DIR objects have been deleted.$(STYLE_NORMAL)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(STYLE_BOLD)$(COLOR_RED)$(NAME) has been deleted.$(STYLE_NORMAL)"

re: fclean all

.PHONY: clean all fclean re