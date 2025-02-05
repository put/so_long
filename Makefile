NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Library paths
MLX42_PATH = ./MLX42
LIBFT_PATH = ./libft
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
MLX42_VERSION = ce254c3
LIBFT_REPO = https://github.com/put/libft.git
LIBFT_VERSION = 3923c01

# Headers and libraries
HEADERS = -I$(MLX42_PATH)/include -I$(LIBFT_PATH)
LIBS = $(MLX42_PATH)/build/libmlx42.a $(LIBFT_PATH)/libft.a -ldl -lglfw -pthread -lm

SRCS = src/cleanup.c src/drawmanipimage.c src/errors.c src/floodfillhelpers.c src/gamelogic.c src/getsetimage.c src/getsetmap.c src/io.c src/locationhelpers.c src/main.c src/maphelpers.c src/mapverification.c src/moremapverification.c
OBJS = $(SRCS:.c=.o)

all: mlx42 libft $(NAME)

mlx42: $(MLX42_PATH)/build/libmlx42.a

$(MLX42_PATH)/build/libmlx42.a:
	@if [ ! -d "$(MLX42_PATH)" ]; then \
		git clone $(MLX42_REPO) $(MLX42_PATH); \
		cd $(MLX42_PATH) && git checkout $(MLX42_VERSION); \
	fi
	@mkdir -p $(MLX42_PATH)/build
	@cd $(MLX42_PATH) && cmake -B build && cmake --build build -j4

libft: $(LIBFT_PATH)/libft.a

$(LIBFT_PATH)/libft.a:
	@if [ ! -d "$(LIBFT_PATH)" ]; then \
		git clone $(LIBFT_REPO) $(LIBFT_PATH); \
		cd $(LIBFT_PATH) && git checkout $(LIBFT_VERSION); \
	fi
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
	@rm -rf $(MLX42_PATH)
	@rm -rf $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re mlx42 libft