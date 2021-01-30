/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 23:03:48 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/20 23:58:11 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int	fuse_trgb(int t, int r, int g, int b)
{
	if (t > 255)
		t = 255;
	else if (t < 0)
		t = 0;
	if (r > 255)
		r = 255;
	else if (t < 0)
		t = 0;
	if (g > 255)
		g = 255;
	else if (t < 0)
		t = 0;
	if (b > 255)
		b = 255;
	else if (t < 0)
		t = 0;
	return (t << 24 | r << 16 | g << 8 | b);
}

int	fuse_vector(t_vector *vec)
{
	return (fuse_trgb(vec->other, vec->x, vec->y, vec->z));
}
