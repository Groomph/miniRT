/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:55:40 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 16:46:11 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_add_back(t_list **first_link, t_list *new_link)
{
	if (!(*first_link))
		*first_link = new_link;
	else if ((*first_link)->next)
		list_add_back(&((*first_link)->next), new_link);
	else
		(*first_link)->next = new_link;
}
