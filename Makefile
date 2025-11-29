# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 20:40:19 by ohaker            #+#    #+#              #
#    Updated: 2025/09/02 20:18:15 by ohaker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -pthread -Werror -Wextra -Wall
SRC = $(addprefix src/, \
	philo.c \
	utils.c \
	checks.c \
	routines.c \
	clean_and_threads.c)
OBJ = $(SRC:.c=.o)

NONE		= \033[0m
GREEN		= \033[32;01m
RED			= \033[31;01m
ORANGE		= \033[33;01m

.SILENT:

all:	$(NAME)

$(NAME): $(OBJ)
	echo "$(ORANGE)		- Compiling $(NAME)...$(NONE)"
	gcc $(CFLAGS) $(OBJ) -lpthread -o $(NAME)
	echo "$(GREEN)		- $(NAME) Compiled -$(NONE)"

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	echo "$(ORANGE)		- Deleted object files$(NONE)"

fclean: clean
	rm -f $(NAME)
	echo "$(ORANGE)		- Deleted $(NAME)$(NONE)"

re: fclean all

mygit:
	git add .
	git status
	echo "$(ORANGE)		- Enter commit message:$(NONE)"; \
	read input; \
	if [ -z "$$input" ]; then \
		echo "$(RED)		- No commit message entered. Exiting.$(NONE)"; \
	else \
		TIMESTAMP=$$(date '+%Y-%m-%d %H:%M'); \
		git commit -m "$$input" -m "Commit date: $$TIMESTAMP"; \
		git push origin master; \
		echo "$(GREEN)		- Pushed to git$(NONE)"; \
	fi

format:
	PATH="$$HOME/.local/bin:$$PATH" find ./ -type f -name "*.[ch]"  -exec c_formatter_42 {} \;

.PHONY: all clean fclean re mygit format