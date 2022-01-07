/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:28:33 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 15:59:56 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	utoa_len(unsigned long long nb, int sizebase)
{
	int	i;

	i = 1;
	nb /= sizebase;
	while (nb)
	{
		nb /= sizebase;
		i++;
	}
	return (i);
}
