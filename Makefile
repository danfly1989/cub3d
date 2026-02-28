NAME = cub3d

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC = src/main.c \
      src/raycasting.c \
      src/raycasting_draw.c \
      src/raycasting_background.c \
      src/input.c \
      src/texture_utils.c \
      src/parse.c \
      src/parse_file.c \
      src/parse_meta.c \
      src/parse_map.c \
      src/parse_validate.c \
      src/cleanup.c \
      src/parse_map_utils.c \
      src/parse_file_utils.c

OBJ = $(SRC:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS  = -lft -lmlx -lm -lXext -lX11 -lpthread -lrt -ldl

.PHONY: all clean fclean re

all: $(MLX_LIB) $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX_DIR):
	@echo "MiniLibX not found, cloning..."
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

$(MLX_LIB): | $(MLX_DIR)
	@echo "Building MiniLibX..."
	make -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(MLX_DIR) ]; then make -C $(MLX_DIR) clean; fi
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@if [ -d $(MLX_DIR) ]; then rm -rf $(MLX_DIR); fi

re: fclean all
