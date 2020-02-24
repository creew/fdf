
NAME = fdf

CC = gcc

CC_FLAGS = -Wall -Wextra $(CC_FLAG_ERR)

CC_FLAG_ERR = -Werror

SRCS =	fdf.c \
		read_map.c \
		init_images.c \
		draw_main.c \
		mouse_moves.c \
		transforms.c \
		getters.c \
		draw_line.c \
		mouse_hook.c \
		key_hook.c \
		colorize_map.c \
		normalize_map.c \
		do_transform.c \
		draw_woo.c \
		other_hooks.c \
		setters.c

OBJS	= $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

SRCDIR	= ./srcs
OBJDIR	= ./objs

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
MINILIBX_DIR = ./minilibx
FRAMEWORKS = -lmlx -lXext -lX11 -lm
endif
ifeq ($(UNAME_S), Darwin)
MINILIBX_DIR = ./minilibx_macos
FRAMEWORKS = -framework OpenGL -framework AppKit
endif

LIBFT_LIB = ft
MINILIBX_LIB = mlx
FT_PRINTF_LIB = ftprintf

LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf
INC_DIR = $(LIBFT_DIR)/includes $(MINILIBX_DIR) $(FT_PRINTF_DIR)/includes ./includes
LINC_DIR = $(LIBFT_DIR) $(MINILIBX_DIR) $(FT_PRINTF_DIR)

IINC = $(addprefix -I,$(INC_DIR))
LINC = $(addprefix -L,$(LINC_DIR))

LLIBS = $(addprefix -l,$(LIBFT_LIB) $(MINILIBX_LIB) $(FT_PRINTF_LIB))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MINILIBX_DIR)
	make -C $(FT_PRINTF_DIR)
	$(CC) $(CC_FLAGS) $(OBJS) $(LINC) $(LLIBS) $(FRAMEWORKS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c includes/fdf.h | $(OBJDIR)
	$(CC) $(CC_FLAGS) $(IINC) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)
	make clean -C $(FT_PRINTF_DIR)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIBFT_DIR)/lib$(LIBFT_LIB).a
	rm -f $(MINILIBX_DIR)/lib$(MINILIBX_LIB).a
	rm -f $(FT_PRINTF_DIR)/lib$(FT_PRINTF_LIB).a
	rm -f $(NAME)

re:	fclean all
