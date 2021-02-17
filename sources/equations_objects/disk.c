/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:16:17 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/12 19:12:44 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>

void	set_disk_normal(t_ray *ray, t_obj *disk)
{
	double		cos;
	t_vector	normal;
	t_point		hit_from_cam;

	hit_from_cam = multiply_vector(&(ray->dir), ray->t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	cos = get_scalar_product(&(disk->normal), &(ray->dir));
	if (cos > 0.0)
	{
		ray->hit_normal = multiply_vector(&(disk->normal), -1);
	}
	else
	{
		ray->hit_normal = disk->normal;
	}
}

/*
   t_point         hit_from_cam;
   t_point         center;
   t_vector        ray_cyl_o;

   hit_from_cam = multiply_vector(&(ray->dir), ray->t);
   ray->hit = add_vectors(&(ray->o), &hit_from_cam);
   center = multiply_vector(&(disk->normal), ray->dist);
   center = add_vectors(&center, &(disk->o));
   if (ray->hit_inside)
   ray->hit_normal = sub_vectors(&center, &(ray->hit));
   else
   ray->hit_normal = sub_vectors(&(ray->hit), &center);
   set_normalized(&(ray->hit_normal));
   */

BOOL	is_intersect_disk(t_ray *ray, t_obj *disk, t_inter *inter)
{
	double		cos;
	t_vector	ray_pl_o;
	double		dist;
	t_vector	hit_point;

	cos = get_scalar_product(&(disk->normal), &(ray->dir));
	if (cos < EPSILON && cos > -EPSILON)
		return (FALSE);
	ray_pl_o = sub_vectors(&(disk->o), &(ray->o));
	inter->t1 = get_scalar_product(&(disk->normal), &(ray_pl_o)) / cos;
	if (inter->t1 < 0)
	       return (FALSE);	
	hit_point = multiply_vector(&(ray->dir), inter->t1);
	hit_point = add_vectors(&(ray->o), &hit_point);
	hit_point = sub_vectors(&(hit_point), &(disk->o));
	dist = sqrt(get_norme(&hit_point));
//	printf("%lf\n", dist);
	if (dist >= disk->radius)
		return (FALSE);
	return (TRUE);
}

/*
	temp_o = multiply_vector((&disk->normal), disk->h);
	temp_o = add_vectors(&(disk->o), &temp_o);
	ray_pl_o = sub_vector(&(temp_o), &(ray->o));
	inter->t2 = get_scalar_product(&(disk->normal), &(ray->o)) / cos;
	hit_point = multiply_vector(&(ray->dir), inter->t1);
	hit_point = add_vectors(&(ray->o), &hit_point);
	hit_point = sub_vectors(&(hit_point), &(disk->o));
	dist = sqrt(get_norme(&hit_point));
	if (inter->t1 < 0 || dist1 > disk->radius)
		inter->t1 = INFINITY;
	hit_point = multiply_vector(&(ray->dir), inter->t2);
	hit_point = add_vectors(&(ray->o), &hit_point);
	hit_point = sub_vectors(&(hit_point), &(temp_o));
	dist = sqrt(get_norme(&hit_point));
	if (inter->t2 < 0 || dist > disk->radius)
		inter->t2 = INFINITY;
*/
