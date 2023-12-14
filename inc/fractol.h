/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:50:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 16:00:40 by ldulling         ###   ########.fr       */
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

/* temporary */
#include <stdio.h>
#include "ft_printf.h"
#include <fcntl.h>

/* Customization */
# define WIN_WIDTH							1920
# define WIN_HEIGHT							980
# define INITIAL_VIEW						1.2
# define MAX_ITERATIONS						100
# define ZOOM_OPTIMIZATION_ON_OFF_DEFAULT	false
# define ZOOM_OPTIMIZATION					90

/* Possible fractals */
# define MANDELBROT		1
# define JULIA			2
# define MULTIBROT		3
# define MULTIJULIA		4
# define BARNSLEYFERN	5

/* Errors */
# define ARG_ERROR		1
# define MLX_ERROR		2

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

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

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
	int			fractal;
	t_complex	c_default;
}	t_data;

typedef struct s_mlx
{
	void	*xvar;
	void	*win;
	void	*img;
	t_data	data;
}	t_mlx;

/* Calculate */
t_complex	calculate_next_iteration(t_complex z, t_complex c);
void		draw_julia(t_data *data, int max_iter, double esc_radius);
void		draw_multijulia(t_data *data, int max_iter, double esc_radius);
void		draw_mandelbrot(t_data *data, int max_iter);
void		draw_multibrot(t_data *data, int max_iter);
void		map_cmplxplane_to_win(t_complex *cmpt, t_data *data, t_coord img);

/* Barnsley Fern */
void		draw_barnsleyfern(t_data *data, int max_iter);
double		get_random_double(int urandom);
void	choose_random_point(double r, double *xn, double *yn);
void		scale_barnsley_point(t_coord *img, double xn, double yn);

/* Color */
int			color(int iter, int max_iter, t_complex z);
int			save_rgb_in_int(double smooth_color);

/* Events */
int			key_handling(int keysymbol, t_mlx *mlx);
int			mouse_handling(int button, int x, int y, t_data *data);
void		zoom_viewport(int x, int y, t_data *data);
void		optimization_configs(int keysymbol, t_mlx *mlx);

/* Exit */
int			clean_exit(t_mlx *mlx, int error);

/* Init */
void		default_view(t_mlx *mlx);
void		init(t_mlx *mlx);

/* Parsing */
bool		parse_arguments(int argc, char *argv[], t_data *data);
bool		setup_mandelbrot(int argc, char *argv[], t_data *data);
bool		setup_julia(int argc, char *argv[], t_data *data);
bool		setup_multibrot(int argc, char *argv[], t_data *data);
bool		setup_multijulia(int argc, char *argv[], t_data *data);
bool		setup_barnsleyfern(int argc, char *argv[], t_data *data);

/* Parsing uils */
bool		parse_julia_values(int argc, char *argv[], t_complex *c_default);
bool		valid_float_arg(char *arg);

/* Rendering */
void		img_pixel_put(t_data *data, int x, int y, int color);
int			render_mandelbrot(t_mlx *mlx);
int			render_julia(t_mlx *mlx);
int			render_multibrot(t_mlx *mlx);
int			render_multijulia(t_mlx *mlx);
int			render_barnsleyfern(t_mlx *mlx);

#endif
