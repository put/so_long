NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Library paths
MLX42_PATH = ./MLX42
LIBFT_PATH = ./libft

# Headers and libraries
HEADERS = -I$(MLX42_PATH)/include -I$(LIBFT_PATH)
LIBS = $(MLX42_PATH)/build/libmlx42.a $(LIBFT_PATH)/libft.a -ldl -lglfw -pthread -lm

SRCS = src/cleanup.c src/drawmanipimage.c src/errors.c src/floodfillhelpers.c src/gamelogic.c src/getsetimage.c src/getsetmap.c src/io.c src/locationhelpers.c src/main.c src/maphelpers.c src/mapverification.c
OBJS = $(SRCS:.c=.o)

all: mlx42 libft $(NAME)

mlx42:
	@rm -rf $(MLX42_PATH)/build
	@mkdir -p $(MLX42_PATH)/build
	@cd $(MLX42_PATH) && cmake -B build && cmake --build build -j4

libft:
	@make all -C $(LIBFT_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJS)
	@rm -rf $(MLX42_PATH)/build

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx42 libft