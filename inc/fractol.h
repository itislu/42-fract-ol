/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:50:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 19:38:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* Customization */
# define WIN_WIDTH							1920
# define WIN_HEIGHT							980
# define INITIAL_VIEW						1.2
# define MAX_ITERATIONS						100
# define MINIMUM_MAX_ITERATIONS				30
# define ZOOM_OPTIMIZE_ON_OFF_DEFAULT		false
# define ZOOM_OPTIMIZE						90

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
	bool	is_zoom_optimize;
	double	zoom_optimize_factor;
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

/* Color */
int			color(int iter, int max_iter, t_complex z);
int			save_rgb_in_int(double smooth_color);

/* Events */
	// Key handling
int			key_handling(int keysymbol, t_mlx *mlx);
void		optimization_configs(int keysymbol, t_mlx *mlx);
	// Mouse handling
int			mouse_handling(int button, int x, int y, t_data *data);
void		zoom_viewport(int x, int y, t_data *data);

/* Fractals */
	// Barnsley Fern
int			render_barnsleyfern(t_mlx *mlx);
void		calc_barnsleyfern(t_data *data, int max_iter);
double		get_random_double(int urandom);
void		choose_random_point(double r, double *xn, double *yn);
void		map_barnsley_point_to_win(t_coord *img, double xn, double yn);
	// Mandelbrot
int			render_mandelbrot(t_mlx *mlx);
void		calc_mandelbrot(t_data *data, int max_iter);
	// Multibrot
int			render_multibrot(t_mlx *mlx);
void		calc_multibrot(t_data *data, int max_iter);
	// Julia
int			render_julia(t_mlx *mlx);
void		calc_julia(t_data *data, int max_iter, double esc_radius);
	// Multijulia
int			render_multijulia(t_mlx *mlx);
void		calc_multijulia(t_data *data, int max_iter, double esc_radius);
	// Calculation utils
t_complex	calc_next_iteration(t_complex z, t_complex c);
t_complex	calc_next_iteration_multi(t_complex z, t_complex c, double n);
void		map_cmplxplane_to_win(t_complex *cmpt, t_data *data, t_coord img);

/* Parsing */
bool		parse_arguments(int argc, char *argv[], t_data *data);
bool		parse_julia_values(int argc, char *argv[], t_complex *c_default);
	// Parsing utils
bool		setup_config(int argc, char *argv[], t_data *data, int fractal);
bool		setup_fixed(int argc, t_data *data, int fractal);
bool		valid_float_arg(char *arg);

/* Utils */
void		img_pixel_put(t_data *data, int x, int y, int color);
void		print_manual(void);
	// Exit
int			clean_exit(t_mlx *mlx, int error);
	// Init
void		default_view(t_mlx *mlx);
void		init(t_mlx *mlx);

#endif
