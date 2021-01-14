/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:56:28 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 18:11:03 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_object(void *object)
{
	if (object)
		free(object);
}

void		list_delone(t_list *list, void (*del)(void*))
{
	if (!del)
		del = &free_object;
	if (list && list->object)
		del(list->object);
	if (list)
		free(list);
}
