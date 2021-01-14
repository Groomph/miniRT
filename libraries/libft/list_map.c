/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:57:16 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 18:09:52 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_object(void *object)
{
	if (object)
		free(object);
}

t_list		*list_map(t_list *list, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_link;
	t_list	*new_link;
	void	*temp_object;

	first_link = NULL;
	if (!del)
		del = &free_object;
	while (list && f)
	{
		temp_object = f(list->object);
		if (temp_object)
			new_link = list_new(temp_object);
		if (!temp_object || !new_link)
		{
			list_clear(&first_link, del);
			if (temp_object)
				del(temp_object);
			return (NULL);
		}
		list_add_back(&first_link, new_link);
		list = list->next;
	}
	return (first_link);
}
