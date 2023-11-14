/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:30 by ldulling          #+#    #+#             */
/*   Updated: 2023/10/22 19:26:31 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnstr_fd(const char *s, size_t n, int fd)
{
	size_t	len;
	ssize_t	written;

	written = 0;
	if (s == NULL || n == 0 || fd < 0)
		return (0);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	written += write(fd, s, len);
	if (written < 0)
		written = 0;
	return ((size_t) written);
}
