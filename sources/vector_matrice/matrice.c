/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 02:50:08 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/03 20:25:05 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vector	get_x_rotation(t_vector *vec, double theta, BOOL is_radian)
{
	double		coss;
	double		sinn;
	t_vector	temp;

	if (!is_radian)
		theta *= PI / 180;
	coss = cos(theta);
	sinn = sin(theta);
	temp.x = vec->x;
	temp.y = coss * vec->y - sinn * vec->z;
	temp.z = sinn * vec->y + coss * vec->z;
	return (temp);
}

t_vector	get_y_rotation(t_vector *vec, double theta, BOOL is_radian)
{
	double		coss;
	double		sinn;
	t_vector	temp;

	if (!is_radian)
		theta *= PI / 180;
	coss = cos(theta);
	sinn = sin(theta);
	temp.x = coss * vec->x + sinn * vec->z;
	temp.y = vec->y;
	temp.z = -(sinn * vec->x) + coss * vec->z;
	return (temp);
}

t_vector	get_z_rotation(t_vector *vec, double theta, BOOL is_radian)
{
	double		coss;
	double		sinn;
	t_vector	temp;

	if (!is_radian)
		theta *= PI / 180;
	coss = cos(theta);
	sinn = sin(theta);
	temp.x = coss * vec->x - sinn * vec->y;
	temp.y = sinn * vec->x + coss * vec->y;
	temp.z = vec->z;
	return (temp);
}

void		set_full_rotation(t_vector *vec, t_vector *dir)
{
	*vec = get_x_rotation(vec, dir->x, TRUE);
	*vec = get_y_rotation(vec, dir->y, TRUE);
	*vec = get_z_rotation(vec, dir->z, TRUE);
}
