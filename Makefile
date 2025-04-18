NAME = cub3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline -lncurses -LIBFTDIR

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
MLXDIR = ./minilibx-linux
MLXLIB = $(MLXDIR)/libmlx.a
INCLUDE = ./includes

MAP_PATH = res/maps/subject.cub
EXE = $(NAME) $(MAP_PATH)


INCLUDES = -I$(INCLUDE) -I$(MLXDIR) -I$(LIBFTDIR)
MLX_FLAGS = -L$(MLXDIR) -lmlx -L/usr/lib/X11 -lXext -lX11

SRCS = $(wildcard *.c) \
		$(wildcard ./main_srcs/*.c) \
		$(wildcard ./libft/*.c) \
		$(wildcard ./gnl/*.c) \
		$(wildcard ./parsing_map/*.c) \

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(MLXLIB)  $(NAME)

$(LIBFT):
	$(MAKE) all -C $(LIBFTDIR)

$(MLXLIB):
	make -C $(MLXDIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -lm -lz

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	make -C $(LIBFTDIR) clean
	make -C $(MLXDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all
