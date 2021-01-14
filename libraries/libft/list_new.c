/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:58:16 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 16:34:59 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*list_new(void *object)
{
	t_list	*link;

	link = malloc(sizeof(t_list));
	if (link)
	{
		link->object = object;
		link->next = NULL;
	}
	return (link);
}
