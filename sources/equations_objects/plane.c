/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:24:18 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/16 14:09:10 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>

void	set_plane_normal(t_ray *ray, t_obj *plane)
{
	double		cos;
	t_vector	normal;
	t_point		hit_from_cam;

	hit_from_cam = multiply_vector(&(ray->dir), ray->t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	cos = get_scalar_product(&(plane->normal), &(ray->dir));
	if (cos > 0.0)
	{
		ray->hit_normal = multiply_vector(&(plane->normal), -1);
	}
	else
	{
		ray->hit_normal = plane->normal;
	}
}

/*
**	printf("ray->hit: %lf, %lf, %lf\n",
**					ray->hit.x, ray->hit.y, ray->hit.z);
**	printf("plane->o: %lf, %lf, %lf\n",
**		plane->plane.o.x, plane->plane.o.y, plane->plane.o.z);
**	printf("ray->hit_normal: %lf, %lf, %lf\n",
**		ray->hit_normal.x, ray->hit_normal.y, ray->hit_normal.z);
**ajouter gestion lumiere au sein d'un objet en comparant si t < 0 et t2 > 0
*/

BOOL	is_intersect_plane(t_ray *ray, t_obj *plane, t_inter *inter)
{
	double		cos;
	t_vector	ray_pl_o;
	double		t;

	cos = get_scalar_product(&(plane->normal), &(ray->dir));
	if (cos < EPSILON && cos > -EPSILON)
		return (FALSE);
	ray_pl_o = sub_vectors(&(plane->o), &(ray->o));
	t = get_scalar_product(&(plane->normal), &ray_pl_o) / cos;
	if (t < 0)
		return (FALSE);
	inter->t1 = t;
	inter->hit_inside = FALSE;
	return (TRUE);
}
