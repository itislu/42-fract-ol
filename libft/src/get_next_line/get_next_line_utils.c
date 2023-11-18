/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:27:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/18 12:20:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	add_new_node(t_list *cur)
{
	cur->next = (t_list *) malloc(sizeof(t_list));
	if (!cur->next)
		return (0);
	cur->next->bytes_unsaved = 0;
	cur->next->line_end = NO_NL;
	cur->next->endoffile = 0;
	cur->next->next = NULL;
	return (1);
}

size_t	count_result_size(t_list *cur)
{
	size_t	result_size;

	result_size = 0;
	while (cur->next)
	{
		result_size += cur->bytes_unsaved;
		cur = cur->next;
	}
	result_size += cur->line_end + 1;
	return (result_size);
}

ssize_t	find_endofline(t_list *cur)
{
	ssize_t	i;

	i = cur->line_end + 1;
	while (cur->buf[i])
	{
		if (cur->buf[i] == '\n')
			return (i);
		i++;
	}
	if (cur->endoffile)
		return (i - 1);
	else
		return (NO_NL);
}

void	free_list(t_list **head)
{
	t_list	*cur;

	while (*head)
	{
		cur = *head;
		*head = (*head)->next;
		free(cur);
	}
	return ;
}

int	initial_check(int fd, t_list **head)
{
	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE < 1)
		return (0);
	if (!*head)
	{
		*head = (t_list *) malloc(sizeof(t_list));
		if (!*head)
			return (0);
		(*head)->buf[0] = '\0';
		(*head)->bytes_unsaved = 0;
		(*head)->line_end = NO_NL;
		(*head)->endoffile = 0;
		(*head)->next = NULL;
	}
	return (1);
}
