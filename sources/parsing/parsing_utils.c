/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:12:47 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/20 23:13:30 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"

int	vector_microparser(t_vector *vector, char *format, int *i)
{
	int		j;
	double	doub[3];

	j = 0;
	while (format[*i] == ' ')
		(*i)++;
	while (j < 3)
	{
		if (format[*i] >= '0' && format[*i] <= '9')
			doub[j] = atodoub_windex(format, i);
		else if (format[(*i) + 1] >= '0' && format[(*i) + 1] <= '9'
							&& format[*i] == '-')
			doub[j] = atodoub_windex(format, i);
		else
			return (0);
		if (j < 2 && format[(*i)++] != ',')
			return (0);
		j++;
	}
	*vector = get_vector(0, doub[0], doub[1], doub[2]);
	return (1);
}

int	double_microparser(double *doub, char *format, int *i)
{
	while (format[*i] == ' ')
		(*i)++;
	if (format[*i] >= '0' && format[*i] <= '9')
		*doub = atodoub_windex(format, i);
	else if (format[(*i) + 1] >= '0' && format[(*i) + 1] <= '9'
						&& format[*i] == '-')
		*doub = atodoub_windex(format, i);
	else
		return (0);
	return (1);
}

int	int_microparser(int *nb, char *format, int *i)
{
	while (format[*i] == ' ')
		(*i)++;
	if (format[*i] >= '0' && format[*i] <= '9')
		*nb = atoi_windex(format, i);
	else if (format[(*i) + 1] >= '0' && format[(*i) + 1] <= '9'
						&& format[*i] == '-')
		*nb = atoi_windex(format, i);
	else
		return (0);
	return (1);
}

int	color_microparser(t_color *color, char *format, int *i)
{
	int	j;
	int	nb[4];

	j = 0;
	while (format[*i] == ' ')
		(*i)++;
	while (j < 4)
	{
		if (format[*i] >= '0' && format[*i] <= '9')
			nb[j] = atoi_windex(format, i);
		else
			return (0);
		if (j < 3 && format[(*i)++] != ',' || nb[j] > 255)
			return (0);
		j++;
	}
	*color = get_vector(nb[0], nb[1], nb[2], nb[3]);
	return (1);
}
