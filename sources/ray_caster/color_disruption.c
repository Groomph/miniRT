/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruption.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:12:11 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/22 18:37:34 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

void	check_board(t_ray *ray)
{
	int	x;

	x = (int)((ray->hit.x + 165413) * 5);
	x += (int)((ray->hit.y + 165413) * 5);
	x += (int)((ray->hit.z + 165413) * 5);
	x %= 2;
	if (x)
	{
		ray->temp_color.x += 20;
		ray->temp_color.y += 20;
		ray->temp_color.z += 20;
		ray->temp_color = multiply_vector(&(ray->temp_color), 2.0);
	}
	else
		ray->temp_color = multiply_vector(&(ray->temp_color), 0.2);
}

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
		ray->temp_color.x = 40;
	if (ray->color.y < 40)
		ray->temp_color.y = 40;
	if (ray->color.z < 40)
		ray->temp_color.z = 40;
	ray->temp_color.x *= normal.x;
	ray->temp_color.y *= normal.y;
	ray->temp_color.z *= normal.z;
}

void	liana(t_point p, t_color *c)
{
	double	d;

	d = noise(p.x, p.y, p.z);
	if (d < 0 && d > -0.1)
	{
		c->x = 0;
		c->y = 255.5;
		c->z = 0;
	}
}

void	perlin(t_point p, t_color *c)
{
	double	d;

	d = noise(p.x, p.y, p.z) * 0.8;
	if (d < 0)
		d = 0.0;
	if (d > 1)
		d = 1.0;
	c->x *= d;
	c->y *= d;
	c->z *= d;
}

void	marbre(t_point p, t_color *c)
{
	double	d;

	d = noise(p.x, p.y, p.z);
	if (d < 0 && d > -0.2)
		d *= -1.0;
	else if (d < 0 && d > -0.4)
		d *= -0.5;
	else if (d < 0)
		d = 0.0;
	if (d > 1)
		d = 1.0;
	c->x *= d;
	c->y *= d;
	c->z *= d;
}
