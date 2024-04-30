
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

// Full HD
// #define WIDTH 1920
// #define HEIGHT 1080

// HD
// #define WIDTH 1280
// #define HEIGHT 720

// Ergodic Billiard
#define WIDTH 1280
#define HEIGHT 721

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;

	t_data	img;
}			t_vars;

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_pixel(t_vars *vars, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	my_mlx_pixel_put(&vars->img, x, y, color);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("keycode: %d\n", keycode);
	return (0);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	printf("mouse move: %d, %d\n", x, y);
	draw_pixel(vars, x, y, 0x00FF0000);
	return (0);
}

int	mouse_down(int key, int x, int y, t_vars *vars)
{
	(void)vars;
	printf("mouse down: [%d] - (%d, %d)\n", key, x, y);
	return (0);
}

int	mouse_up(int key, int x, int y, t_vars *vars)
{
	(void)vars;
	printf("mouse up: [%d] - (%d, %d)\n", key, x, y);
	return (0);
}

int	window_close(t_vars *vars)
{
	printf("window close\n");
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	loop_hook(t_vars *vars)
{
	static int	n;
	int			x;
	int			y;

	x = n % (2 * WIDTH);
	y = n % (2 * HEIGHT);
	if (x > WIDTH)
		x = 2 * WIDTH - x;
	if (y > HEIGHT)
		y = 2 * HEIGHT - y;
	draw_pixel(vars, x, y, 0x0000FF00);
	n = (n + 2) % (WIDTH * HEIGHT);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "sample");
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	mlx_hook(vars.win, ON_MOUSEMOVE, 0, mouse_move, &vars);
	mlx_hook(vars.win, ON_MOUSEDOWN, 0, mouse_down, &vars);
	mlx_hook(vars.win, ON_MOUSEUP, 0, mouse_up, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, window_close, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
