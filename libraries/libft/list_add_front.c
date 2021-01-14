/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:55:53 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 16:32:35 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_add_front(t_list **first_link, t_list *new_link)
{
	if (first_link && new_link)
	{
		new_link->next = *first_link;
		*first_link = new_link;
	}
}
