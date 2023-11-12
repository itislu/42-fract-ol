#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* Not yet needed */
#include <math.h>

/* Not needed */
#include <stdio.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define MLX_ERROR 1

typedef struct	s_mlx
{
	void	*xvar;
	void	*win;
	void	*img;
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
}	t_mlx;

typedef struct	s_complex
{
	double	real;
	double	imag;
}	t_complex;

#endif
