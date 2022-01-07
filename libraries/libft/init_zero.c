/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:23:49 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 16:01:10 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_zero(void *pt, size_t n)
{
	unsigned char	*tempt;
	size_t			i;

	tempt = (unsigned char *)pt;
	i = 0;
	while (i < n)
	{
		tempt[i] = '\0';
		i++;
	}
}
