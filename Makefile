##
## Makefile for makefile in /home/zellou_i/rendu/PSU_2013_myftp
## 
## Made by ilyas zelloufi
## Login   <zellou_i@epitech.net>
## 
## Started on  Sun Apr 13 11:03:49 2014 ilyas zelloufi
## Last update Sun Apr 13 21:25:24 2014 ilyas zelloufi
##

CC =		gcc

RM =		rm -f

CFLAGS +=

LDFLAGS =

NAME_SERVER =	serveur

NAME_CLIENT =	client

SRCS_SERVER =	serveur.c \
		cmd.c \
		my_str_to_wordtab.c

SRCS_CLIENT =	client.c \
		my_str_to_wordtab.c

OBJS_SERVER =	$(SRCS_SERVER:.c=.o)

OBJS_CLIENT =	$(SRCS_CLIENT:.c=.o)

all:		$(NAME_SERVER) $(NAME_CLIENT)

server:		$(NAME_SERVER)

client:		$(NAME_CLIENT)

$(NAME_SERVER):	$(OBJS_SERVER)
		$(CC) $(OBJS_SERVER) -o $(NAME_SERVER) $(LDFLAGS)

$(NAME_CLIENT):	$(OBJS_CLIENT)
		$(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)

clean:
		$(RM) $(OBJS_SERVER)
		$(RM) $(OBJS_CLIENT)

fclean:		clean
		$(RM) $(NAME_SERVER)
		$(RM) $(NAME_CLIENT)

re:		fclean all

.PHONY:		all clean fclean re
