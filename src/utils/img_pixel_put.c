/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:46:50 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 17:51:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pixel_put(t_data *data, int x, int y, int color)
{
	int		bytes_per_pixel;
	int		i;
	int		next_byte;
	char	*pixel;

	bytes_per_pixel = data->bits_per_pixel / 8;
	pixel = data->addr + (y * data->size_line + x * bytes_per_pixel);
	if (data->endian)
	{
		i = data->bits_per_pixel - 8;
		next_byte = -8;
	}
	else
	{
		i = 0;
		next_byte = 8;
	}
	while (bytes_per_pixel--)
	{
		*pixel++ = (color >> i) & 0XFF;
		i += next_byte;
	}
}
