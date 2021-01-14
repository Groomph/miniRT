/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:28:33 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:28:35 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	utoa_len(unsigned long long nb, int sizebase)
{
	int	i;

	i = 1;
	while (nb /= sizebase)
		i++;
	return (i);
}
