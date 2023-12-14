/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:33:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 17:39:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	setup_config(int argc, char *argv[], t_data *data, int fractal)
{
	bool	success;

	data->fractal = fractal;
	success = parse_julia_values(argc, argv, &data->c_default);
	return (success);
}

bool	setup_fixed(int argc, t_data *data, int fractal)
{
	data->fractal = fractal;
	if (argc > 2)
		ft_printf("%s\n", "No need for additional arguments ;)");
	return (true);
}

bool	valid_float_arg(char *arg)
{
	size_t	len_arg;
	size_t	len_valid;

	len_arg = ft_strlen(arg);
	len_valid = 0;
	while (ft_isspace(arg[len_valid]))
		len_valid++;
	if (arg[len_valid] == '-' || arg[len_valid] == '+')
		len_valid++;
	while (ft_isdigit(arg[len_valid]))
		len_valid++;
	if (arg[len_valid] == '.')
	{
		len_valid++;
		while (ft_isdigit(arg[len_valid]))
			len_valid++;
	}
	if (len_valid == len_arg)
		return (true);
	return (false);
}
