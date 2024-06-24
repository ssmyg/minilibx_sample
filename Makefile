NAME=sample
CFLAGS=-Wall -Wextra -Werror
SRCS=src/main.c
OBJS=$(SRCS:.c=.o)

# minilibx
MINILIBX_URL := https://cdn.intra.42.fr/document/document/23420/minilibx_opengl.tgz
MINILIBX_TAR_GZ := minilibx_opengl.tgz
MINILIBX_DIR := ./minilibx_opengl_20191021
MINILIBX := $(MINILIBX_DIR)/libmlx.a

INCLUDES := -I$(MINILIBX_DIR)
LDFLAGS := -L$(MINILIBX_DIR)
LIBS=-lm -lmlx

.PHONY: all
all: $(NAME)

$(NAME): $(MINILIBX) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MINILIBX_TAR_GZ):
	curl -O $(MINILIBX_URL)

$(MINILIBX): $(MINILIBX_TAR_GZ)
	tar xvzf $(MINILIBX_TAR_GZ)
	$(MAKE) -j4 -C $(MINILIBX_DIR)

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(MINILIBX_DIR) clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(MINILIBX_DIR)
	$(RM) $(MINILIBX_TAR_GZ)

.PHONY: re
re: fclean all
