/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:33:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 13:49:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	parse_julia_values(int argc, char *argv[], t_complex *c_default)
{
	if (argc == 2)
	{
		c_default->real = -0.79;
		c_default->imag = 0.23;
		return (true);
	}
	else if (argc == 3)
	{
		if (valid_float_arg(argv[2]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = c_default->real;
			return (true);
		}
	}
	else
	{
		if (valid_float_arg(argv[2]) && valid_float_arg(argv[3]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = ft_atof(argv[3]);
			return (true);
		}
	}
	return (false);
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
