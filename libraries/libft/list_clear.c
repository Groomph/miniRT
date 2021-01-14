/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:56:08 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 18:04:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_object(void *object)
{
	if (object)
		free(object);
}

void	list_clear(t_list **list, void (*del)(void *))
{
	if (!del)
		del = &free_object;
	if (list && *list)
	{
		list_clear(&((*list)->next), del);
		del((*list)->object);
		free(*list);
		*list = NULL;
	}
}
