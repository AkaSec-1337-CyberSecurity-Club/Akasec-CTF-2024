HEADERSS		=	headers/elf.h\
					headers/header.h\
					headers/parser.h

NAME			=	packeta

MAIN			=	main.c

SRCS			=	src/encryption.c\
  					src/main.c\
    				src/parser.c\
					src/RC4.c\
		 		    src/tools.c


OBJS			=	$(SRCS:.c=.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror  -s

RM				=	rm -f

%.o:%.c			$(HEADERS) 
				$(CC) $(CFLAGS)  -c $< -o $@ 

$(NAME):		$(HEADERS) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS)  -o $(NAME) 

all:			$(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re