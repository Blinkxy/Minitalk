SERVER = server
CLIENT = client
SERVER.BONUS = server_bonus
CLIENT.BONUS = client_bonus
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
CC = cc
LIBFT_A = libft/libft.a

all: $(SERVER) $(CLIENT)
	@echo --- Ready !!! ---	

$(SERVER):
	@make -C Libft
	@$(CC) $(CFLAGS) server.c $(LIBFT_A) -o $(SERVER)
	@echo --- Server up ---

$(CLIENT):
	@$(CC) $(CFLAGS) client.c libft/libft.a -o $(CLIENT)
	@echo --- Client up ---

$(SERVER.BONUS):
	@make -C Libft
	@$(CC) $(CFLAGS) server_bonus.c $(LIBFT_A) -o $(SERVER.BONUS)
	@echo --- Bonus Server up ---

$(CLIENT.BONUS):
	@$(CC) $(CFLAGS) client.bonus.c libft/libft.a -o $(CLIENT.BONUS)
	@echo --- Bonus Client up ---

bonus: $(CLIENT.BONUS) $(SERVER.BONUS)
	@echo --- Bonus Ready !!! ---

clean:	
	@make clean -s -C libft

fclean: clean
	@$(RM) $(SERVER) $(CLIENT) $(CLIENT.BONUS) $(SERVER.BONUS)
	@make clean -s -C libft
	@echo ---server and client cleaned---

re: fclean all

.PHONY: all clean fclean re

