/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:33:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 11:34:13 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	parse_arguments(int argc, char *argv[], t_data *data)
{
	if (argc < 2)
		return (0);
	if (ft_strmatches_any(argv[1], 4, "m", "M", "mandelbrot", "Mandelbrot"))
	{
		data->set = MANDELBROT;
		if (argc > 2)
			ft_printf("%s\n", "No need for additional arguments ;)");
		return (1);
	}
	if (ft_strmatches_any(argv[1], 4, "j", "J", "julia", "Julia"))
	{
		data->set = JULIA;
		if (argc == 2)
		{
			data->c_default.real = -0.79;
			data->c_default.imag = 0.23;
		}
		else if (!parse_julia_values(argc, argv, &data->c_default))
			return (0);
		return (1);
	}
	return (0);
}

int	parse_julia_values(int argc, char *argv[], t_complex *c_default)
{
	if (argc == 3)
	{
		if (valid_float_arg(argv[2]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = c_default->real;
			return (1);
		}
	}
	else
	{
		if (valid_float_arg(argv[2]) && valid_float_arg(argv[3]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = ft_atof(argv[3]);
			return (1);
		}
	}
	return (0);
}

int	valid_float_arg(char *arg)
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
		return (1);
	return (0);
}
