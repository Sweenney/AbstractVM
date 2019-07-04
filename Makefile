# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdemay <tdemay@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/24 16:07:53 by tdemay            #+#    #+#              #
#    Updated: 2015/04/22 14:07:48 by tdemay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	avm

NAMEBASE	=	$(shell basename $(NAME))

OS := $(shell uname)

ifeq ($(OS),Darwin)        # Mac OS X

CC			=	clang++

FLAGS		=	-std=c++11 -stdlib=libc++ -Wall -Wextra -Werror

endif
ifeq ($(OS),Linux)

CC			=	g++

FLAGS		=	-lstdc++ -std=gnu++11 -Wall -Wextra -Werror -g

endif

LIBS		=

SRCBASE		=	\
				avm.cpp \
				Calculator.cpp \
				Int8_t.cpp \
				Int16_t.cpp \
				Int32_t.cpp \
				Float_t.cpp \
				Double_t.cpp

HDS			=	\
				Calculator.hpp \
				Int8_t.hpp \
				Int16_t.hpp \
				Int32_t.hpp \
				Float_t.hpp \
				Double_t.hpp

SRCS		=	$(SRCBASE)

OBJS		=	$(SRCBASE:.cpp=.o)

.SILENT:

all: $(NAME)
	echo "\033[38;5;44m✅  ALL    $(NAMEBASE) is done\033[0m\033[K"

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LIBS) -o $(NAME) $(OBJS)
	echo -en "\r\033[38;5;22m✅  MAKE   $(NAMEBASE)\033[0m\033[K"

$(OBJS): $(SRCS) $(HDS)
	printf "\r\033[38;5;11m⌛  MAKE   $(NAMEBASE) plz wait ...\033[0m\033[K"
	$(CC) $(FLAGS) $(LIBS) -c $(SRCS)

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAMEBASE) plz wait ...\033[0m\033[K"
	if [[ `rm $(OBJS) &> /dev/null 2>&1; echo $$?` == "0" ]]; then           \
		echo -en "\r\033[38;5;124m🔘  CLEAN  $(NAMEBASE)\033[0m\033[K";      \
	else                                                                     \
		printf "\r";                                                         \
	fi

fclean: clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAMEBASE) plz wait ...\033[0m\033[K"
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then           \
		echo -en "\r\033[38;5;124m🔘  FCLEAN $(NAMEBASE)\033[0m\033[K";      \
	else                                                                     \
		printf "\r";                                                         \
	fi

re:			fclean all

.PHONY:		fclean clean re
