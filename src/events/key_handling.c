/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:38:43 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 19:39:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handling(int keysymbol, t_mlx *mlx)
{
	static int	prev_is_zoom_optimize = -1;

	if (prev_is_zoom_optimize == -1)
		prev_is_zoom_optimize = mlx->data.toggle.is_zoom_optimize;
	if (keysymbol == XK_Escape)
		clean_exit(mlx, 0);
	else if (keysymbol == XK_KP_Enter)
	{
		mlx->data.toggle.is_zoom_optimize ^= 1;
		if (mlx->data.max_iter == MAX_ITERATIONS)
			prev_is_zoom_optimize = mlx->data.toggle.is_zoom_optimize;
	}
	else if (keysymbol == XK_KP_Add || keysymbol == XK_KP_Subtract
		|| (keysymbol >= XK_KP_Home && keysymbol <= XK_KP_Insert))
	{
		optimization_configs(keysymbol, mlx);
		if (mlx->data.max_iter >= MAX_ITERATIONS)
			mlx->data.toggle.is_zoom_optimize = prev_is_zoom_optimize;
		else if (mlx->data.max_iter < MINIMUM_MAX_ITERATIONS)
			mlx->data.max_iter = MINIMUM_MAX_ITERATIONS;
		mlx->data.redraw_needed = true;
	}
	return (0);
}

void	optimization_configs(int keysymbol, t_mlx *mlx)
{
	if (keysymbol == XK_KP_Add)
		mlx->data.max_iter *= 1.5;
	else if (keysymbol == XK_KP_Subtract)
		mlx->data.max_iter *= 2.0 / 3.0;
	else if (keysymbol == XK_KP_Insert)
		mlx->data.max_iter = MAX_ITERATIONS;
	else if (keysymbol == XK_KP_End)
		mlx->data.max_iter = MINIMUM_MAX_ITERATIONS;
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
}
