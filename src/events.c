/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:38:43 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 18:59:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handling(int keysymbol, t_mlx *mlx)
{
	// printf("%x\n", keysymbol);
	if (keysymbol == XK_Escape)
		clean_exit(mlx, 0);
	else if (keysymbol == XK_o)
		mlx->data.toggle.zoom_optimization ^= 1;
	return (0);
}

int	zoom(int button, int x, int y, t_data *data)
{
	double	mouse_x_percent;
	double	mouse_y_percent;
	double	x_range;
	double	y_range;

	if (button == Button4)
		data->zoom_factor = 0.95;
	else if (button == Button5)
		data->zoom_factor = 1.05;
	else
		return (0);
	mouse_x_percent = (double)x / WIN_WIDTH;
	mouse_y_percent = (double)y / WIN_HEIGHT;
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
	if (data->max_iter == MAX_ITERATIONS && data->toggle.zoom_optimization)
		data->max_iter *= 1 - (double) ZOOM_OPTIMIZATION / 100;
	data->redraw_needed = true;
	return (0);
}
