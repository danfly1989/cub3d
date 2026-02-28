NAME = cub3d

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC = src/main.c src/raycasting.c src/raycasting_background.c src/input.c src/texture_utils.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS = -lft -lmlx -lm -lXext -lX11 -lpthread -lrt -ldl

.PHONY: all clean fclean re

all: $(MLX_LIB) $(LIBFT) $(NAME)

# Build libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Clone MiniLibX if missing
$(MLX_DIR):
	@echo "MiniLibX not found, cloning..."
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

# Build MiniLibX
$(MLX_LIB): | $(MLX_DIR)
	@echo "Building MiniLibX..."
	make -C $(MLX_DIR)

# Compile executable
$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile objects
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
# Clean
clean:
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(MLX_DIR) ]; then make -C $(MLX_DIR) clean; fi
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@if [ -d $(MLX_DIR) ]; then rm -rf $(MLX_DIR); fi

re: fclean all
