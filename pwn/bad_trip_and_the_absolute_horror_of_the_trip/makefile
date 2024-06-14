SRC = main.c
NAME = bad_trip
CFLAGS = -Wl,-z,relro,-z,now

$(NAME): $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
