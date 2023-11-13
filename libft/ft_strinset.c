/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:50:45 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/13 20:30:08 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strinset(const char *str, const char *set[], size_t set_size)
{
	size_t	i;

	i = 0;
	while (i < set_size)
		if (ft_strcmp(str, set[i]) == 0)
			return (1);
	return (0);
}
