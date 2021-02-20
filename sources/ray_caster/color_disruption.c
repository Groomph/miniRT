/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruption.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:12:11 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/19 15:03:52 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"

void	check_board(t_ray *ray)
{
	int	x;

	x = (int)((ray->hit.x + 165413) * 5);
	x += (int)((ray->hit.y + 165413) * 5);
	x += (int)((ray->hit.z + 165413) * 5);
	x %= 2;
	if (x)
	{
		ray->color.x += 20;
		ray->color.y += 20;
		ray->color.z += 20;
		ray->color = multiply_vector(&(ray->color), 2.0);
	}
	else
		ray->color = multiply_vector(&(ray->color), 0.2);
}

/*
**	y = y % 2;
**	z = z % 2;
**	if (x && !y && !z)
**		ray->color = multiply_vector(&(ray->color), 0.2);
**	else if (!x && y && !z)
**		ray->color = multiply_vector(&(ray->color), 0.2);
**	else if (!x && !y && z)
**		ray->color = multiply_vector(&(ray->color), 0.2);
**	else
**		ray->color = multiply_vector(&(ray->color), 2);
*/

void	rainbow(t_ray *ray, int type)
{
	t_vector	normal;
	double		scalar;

	scalar = 2.0 * get_scalar_product(&(ray->dir), &(ray->hit_normal));
	normal = multiply_vector(&(ray->hit_normal), scalar);
	normal = sub_vectors(&(ray->dir), &normal);
	if (!(type == SPHERE || type == CYLINDER || type == CONE))
		normal = add_vectors(&normal, &(ray->hit));
	set_normalized(&normal);
	if (normal.x < 0.0)
		normal.x *= -1;
	if (normal.y < 0.0)
		normal.y *= -1;
	if (normal.z < 0.0)
		normal.z *= -1;
	if (ray->color.x < 40)
		ray->color.x = 40;
	if (ray->color.y < 40)
		ray->color.y = 40;
	if (ray->color.z < 40)
		ray->color.z = 40;
	ray->color.x *= normal.x;
	ray->color.y *= normal.y;
	ray->color.z *= normal.z;
}

/*
**	normal = ray->hit_normal;
**
**
**	if (ray->nearest_object->type == SPHERE
**			|| ray->nearest_object->type == CYLINDER
**				|| ray->nearest_object->type == CONE)
**		normal = ray->hit_normal;
**	else
**		normal = add_vectors(&(ray->hit_normal), &(ray->hit));
**	if (normal.x < 0.0)
**		normal.x *= -1;
**	if (normal.y < 0.0)
**		normal.y *= -1;
**	if (normal.z < 0.0)
**		normal.z *= -1;
**	if (ray->color.x < 100)
**		ray->color.x = 100;
**	if (ray->color.y < 100)
**		ray->color.y = 1000;
**	if (ray->color.z < 100)
**		ray->color.z = 100;
**	ray->color.x *= normal.x;
**	ray->color.y *= normal.y;
**	ray->color.z *= normal.z;
**}
*/
