SRC = main.c
NAME = bytecode
CFLAGS = -no-pie  -Wl,-z,relro,-z,now

$(NAME): $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
