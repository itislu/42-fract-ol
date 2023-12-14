/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:50:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 18:59:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* Not yet needed */
#include <math.h>

/* temporary */
#include <stdio.h>
#include "ft_printf.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 980
# define INITIAL_VIEW 1.1
# define MAX_ITERATIONS 1000
# define ZOOM_OPTIMIZATION 90
# define ARG_ERROR 1
# define MLX_ERROR 2
# define MANDELBROT 1
# define JULIA 2

typedef struct s_toggle
{
	bool	is_zoom_optimization;
	double	zoom_optimization_factor;
}	t_toggle;

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_data
{
	char		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			color;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		zoom_factor;
	bool		redraw_needed;
	int			max_iter;
	t_toggle	toggle;
	int			set;
	t_complex	c_default;
}	t_data;

typedef struct s_mlx
{
	void	*xvar;
	void	*win;
	void	*img;
	t_data	data;
}	t_mlx;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/* Calculate */
t_complex	calculate_next_iteration(t_complex z, t_complex c);
void		draw_julia(t_data *data, int max_iter, double esc_radius);
void		draw_mandelbrot(t_data *data, int max_iter);
void		map_cmplxplane_to_win(t_complex *cmpt, t_data *data, t_coord coord);

/* Color */
int			color(int iter, int max_iter, t_complex z);
int			save_rgb_in_int(double smooth_color);

/* Events */
int			key_handling(int keysymbol, t_mlx *mlx);
int			zoom(int button, int x, int y, t_data *data);

/* Exit */
int			clean_exit(t_mlx *mlx, int error);

/* Init */
void		default_view(t_mlx *mlx);
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
