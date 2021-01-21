/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atodoub_windex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:00:15 by romain            #+#    #+#             */
/*   Updated: 2021/01/18 03:09:13 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	atodoub_windex(const char *str, int *i)
{
	double	doub;
	double	decipart;

	decipart = 0.1;
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '-')
		decipart = -0.1;
	doub = atoi_windex(str, i);
	if (str[*i] == '.')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		doub += decipart * (str[*i] - '0');
		decipart /= 10;
		(*i)++;
	}
	return (doub);
}
