/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:38:43 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 18:26:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	if (data->toggle.is_zoom_optimize)
		data->toggle.zoom_optimize_factor
			= 1.0 - (double) zoom_optimize / 100;
	data->redraw_needed = true;
}
