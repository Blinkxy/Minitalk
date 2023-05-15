SERVER = server
CLIENT = client
SERVER.BONUS = server_bonus
CLIENT.BONUS = client_bonus
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
CC = cc
LIBFT_A = libft/libft.a
OBJ.SERVER = server.c
OBJ.CLIENT = client.c
OBJ.SERVER.BONUS = server_bonus.c 
OBJ.CLIENT.BONUS = client_bonus.C
SRC.SERVER = $(OBJ.SERVER:.c=.o)
SRC.CLIENT = $(OBJ.CLIENT:.c=.o)
SRC.SERVER.B = $(OBJ.SERVER.BONUS:.c=.o)
SRC.CLIENT.B = $(OBJ.CLIENT.BONUS:.c=.o)

all: $(SERVER) $(CLIENT)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(SRC.SERVER)
	@make -C Libft
	@$(CC) $(CFLAGS) server.c $(LIBFT_A) -o $(SERVER)
	@echo --- Server up ---

$(CLIENT): $(SRC.CLIENT)
	@$(CC) $(CFLAGS) client.c $(LIBFT_A) -o $(CLIENT)
	@echo --- Client up ---

$(SERVER.BONUS): $(SRC.SERVER.B)
	@make -C Libft
	@$(CC) $(CFLAGS) server_bonus.c $(LIBFT_A) -o $(SERVER.BONUS)
	@echo --- Bonus Server up ---

$(CLIENT.BONUS): $(SRC.CLIENT.B)
	@$(CC) $(CFLAGS) client_bonus.c $(LIBFT_A) -o $(CLIENT.BONUS)
	@echo --- Bonus Client up ---

bonus: $(SERVER.BONUS) $(CLIENT.BONUS)

clean:	
	@$(RM) *.o

fclean: clean
	@$(RM) $(SERVER) $(CLIENT) $(CLIENT.BONUS) $(SERVER.BONUS)
	@make fclean -s -C libft
	@echo --- cleaned ---

re: fclean all

.PHONY: all clean fclean re

