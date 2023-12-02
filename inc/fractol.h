#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* Not yet needed */
#include <math.h>

/* temporary */
#include <stdio.h>
#include "ft_printf.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define ARG_ERROR 1
# define MLX_ERROR 2
# define MANDELBROT 1
# define JULIA 2

typedef struct	s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct	s_data
{
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		color;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	zoom_factor;
	int		redraw_needed;
	int		set;
	t_complex	c_default;
}	t_data;

typedef struct	s_mlx
{
	void	*xvar;
	void	*win;
	void	*img;
	t_data	data;
}	t_mlx;

typedef struct	s_coord
{
	int	x;
	int	y;
}	t_coord;

/* Calculate */
t_complex	calculate_next_iteration(t_complex z, t_complex c);
void		draw_julia(t_data *data, int max_iter, double esc_radius);
void		draw_mandelbrot(t_data *data, int max_iter);
void		map_complexplane_to_window(t_complex *cmpt, t_data *data, t_coord coord);

/* Color */
int	color(int iter, int max_iter, t_complex z);

/* Exit */
int			clean_exit(t_mlx *mlx, int error);

/* Interface */
int			key_handling(int keysymbol, t_mlx *mlx);
int			zoom(int button, int x, int y, t_data *data);

/* Init */
void		init(t_mlx *mlx);

/* Parsing */
int			parse_arguments(int argc, char *argv[], t_data *data);
int			parse_julia_values(int argc, char *argv[], t_complex *c_default);
int			valid_float_arg(char *arg);

/* Rendering */
void		img_pixel_put(t_data *data, int x, int y, int color);
int			render_mandelbrot(t_mlx *mlx);
int			render_julia(t_mlx *mlx);

#endif
