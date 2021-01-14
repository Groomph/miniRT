/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:23:49 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:24:14 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_zero(void *pt, size_t n)
{
	unsigned char	*tempt;

	tempt = (unsigned char*)pt;
	while (n--)
		*tempt++ = '\0';
}
