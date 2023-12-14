/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:38:43 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 15:12:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handling(int keysymbol, t_mlx *mlx)
{
	static int	prev_is_zoom_optimization = -1;

	printf("%x\n", keysymbol);	// Delete
	if (prev_is_zoom_optimization == -1)
		prev_is_zoom_optimization = mlx->data.toggle.is_zoom_optimization;
	if (keysymbol == XK_Escape)
		clean_exit(mlx, 0);
	else if (keysymbol == XK_o)
	{
		mlx->data.toggle.is_zoom_optimization ^= 1;
		if (mlx->data.max_iter == MAX_ITERATIONS)
			prev_is_zoom_optimization = mlx->data.toggle.is_zoom_optimization;
	}
	else if (keysymbol == XK_KP_Add || keysymbol == XK_KP_Subtract
		|| (keysymbol >= XK_KP_Home && keysymbol <= XK_KP_Insert))
	{
		optimization_configs(keysymbol, mlx);
		if (mlx->data.max_iter >= MAX_ITERATIONS)
			mlx->data.toggle.is_zoom_optimization = prev_is_zoom_optimization;
		mlx->data.redraw_needed = true;
	}
	return (0);
}

int	mouse_handling(int button, int x, int y, t_data *data)
{
	if (button == Button4)
		data->zoom_factor = 0.95;
	else if (button == Button5)
		data->zoom_factor = 1.05;
	else
		return (0);
	if (data->fractal != BARNSLEYFERN)
		zoom_viewport(x, y, data);
	return (0);
}

void	zoom_viewport(int x, int y, t_data *data)
{
	double	mouse_x_percent;
	double	mouse_y_percent;
	double	x_range;
	double	y_range;

	mouse_x_percent = (double) x / WIN_WIDTH;
	mouse_y_percent = (double) y / WIN_HEIGHT;
	x_range = data->x_max - data->x_min;
	y_range = data->y_max - data->y_min;
	data->x_min = data->x_min
		+ x_range * (1 - data->zoom_factor) * mouse_x_percent;
	data->x_max = data->x_min
		+ x_range * data->zoom_factor;
	data->y_min = data->y_min
		+ y_range * (1 - data->zoom_factor) * mouse_y_percent;
	data->y_max = data->y_min
		+ y_range * data->zoom_factor;
	if (data->toggle.is_zoom_optimization)
		data->toggle.zoom_optimization_factor = 1.0 - (double) ZOOM_OPTIMIZATION / 100;
	data->redraw_needed = true;
}

/* Keypad 1-9 should switch between zoom_opt configs, 0 reset to default, + and - go through them */
void	optimization_configs(int keysymbol, t_mlx *mlx)
{
	if (keysymbol == XK_KP_Add)
		mlx->data.max_iter *= 1.5;
	else if (keysymbol == XK_KP_Subtract)
		mlx->data.max_iter *= 2.0 / 3.0;
	else if (keysymbol == XK_KP_Insert)
		mlx->data.max_iter = MAX_ITERATIONS;
	else if (keysymbol == XK_KP_End)
		mlx->data.max_iter = 30;
	else if (keysymbol == XK_KP_Down)
		mlx->data.max_iter = MAX_ITERATIONS * 0.1;
	else if (keysymbol == XK_KP_Page_Down)
		mlx->data.max_iter = MAX_ITERATIONS * 0.2;
	else if (keysymbol == XK_KP_Left)
		mlx->data.max_iter = MAX_ITERATIONS * 0.33;
	else if (keysymbol == XK_KP_Begin)
		mlx->data.max_iter = MAX_ITERATIONS * 0.5;
	else if (keysymbol == XK_KP_Right)
		mlx->data.max_iter = MAX_ITERATIONS * 1.5;
	else if (keysymbol == XK_KP_Home)
		mlx->data.max_iter = MAX_ITERATIONS * 2;
	else if (keysymbol == XK_KP_Up)
		mlx->data.max_iter = MAX_ITERATIONS * 5;
	else if (keysymbol == XK_KP_Page_Up)
		mlx->data.max_iter = MAX_ITERATIONS * 10;
	if (mlx->data.max_iter < 30)
		mlx->data.max_iter = 30;
}
