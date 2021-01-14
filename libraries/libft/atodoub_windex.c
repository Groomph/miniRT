/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atodoub_windex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:00:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/27 19:32:58 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	atodoub_windex(const char *str, int *i)
{
	double	doub;
	double	decipart;

	doub = atoi_windex(str, i);
	if (str[*i] == '.')
		(*i)++;
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		decipart = atoi_windex(str, i);
		while (decipart >= 1.0)
			decipart /= 10;
		doub += decipart;
	}
	return (doub);
}
