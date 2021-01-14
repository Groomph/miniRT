/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:56:44 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/09 16:47:01 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_iter(t_list *list, void (*f)(void *, void *), void *obj)
{
	if (!list)
		return ;
	f(list->object, obj);
	list_iter(list->next, f, obj);
}
