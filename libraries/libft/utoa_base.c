/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:28:18 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:28:20 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	utoa_base(unsigned long long int nb, char *dest, char *base, int sizebase)
{
	int	size;
	int	i;

	if (!sizebase)
		sizebase = string_len(base);
	size = utoa_len(nb, sizebase);
	i = size;
	dest[i] = '\0';
	while (--i >= 0)
	{
		dest[i] = base[nb % sizebase];
		nb /= sizebase;
	}
	return (size);
}
