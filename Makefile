NAME=sample
CFLAGS=-Wall -Wextra -Werror
SRCS=src/main.c
OBJS=$(SRCS:.c=.o)

MINILIBX_DIR := ./minilibx_opengl_20191021
MINILIBX := $(MINILIBX_DIR)/libmlx.a

INCLUDES := -I$(MINILIBX_DIR)
LDFLAGS := -L$(MINILIBX_DIR)
LIBS=-lm -lmlx

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(MINILIBX)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MINILIBX):
	$(MAKE) -j4 -C $(MINILIBX_DIR)

.PHONY: clean
clean:
	$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MINILIBX_DIR) clean

.PHONY: re
re: fclean all
