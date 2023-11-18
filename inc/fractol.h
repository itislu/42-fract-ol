#ifndef FRACTOL_H
# define FRACTOL_H

//# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* Not yet needed */
#include <math.h>

/* temporary */
#include <stdio.h>
#include "libft/inc/libft.h"

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
	char	*data;
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

#endif
