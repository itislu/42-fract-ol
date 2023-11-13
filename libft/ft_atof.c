/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:15:31 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/13 15:49:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double	decimal_places(const char *nptr);

double	ft_atof(const char *nptr)
{
	double	n;
	int		sign;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	n = 0;
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		if (ft_isdigit(*nptr))
			n += decimal_places(nptr);
	}
	return (n * sign);
}

static double	decimal_places(const char *nptr)
{
	double	n;
	double	fraction;

	n = 0;
	fraction = 0.1;
	while (ft_isdigit(*nptr))
	{
		n += (*nptr - '0') * fraction;
		fraction /= 10;
		nptr++;
	}
	return (n);
}
