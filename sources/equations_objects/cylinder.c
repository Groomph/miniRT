/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:24:18 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 15:01:48 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void	set_cylinder_normal(t_ray *ray, t_obj *cylinder)
{
	t_point		hit_from_cam;
	t_point		center;

	hit_from_cam = multiply_vector(&(ray->dir), ray->t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	center = multiply_vector(&(cylinder->normal), ray->dist);
	center = add_vectors(&center, &(cylinder->o));
	if (ray->hit_inside)
		ray->hit_normal = sub_vectors(&center, &(ray->hit));
	else
		ray->hit_normal = sub_vectors(&(ray->hit), &center);
	set_normalized(&(ray->hit_normal));
}

/*
**	printf("ray->hit: %lf, %lf, %lf\n",
**					ray->hit.x, ray->hit.y, ray->hit.z);
**	printf("cylinder->o: %lf, %lf, %lf\n", cylinder->cylinder.o.x,
**				cylinder->cylinder.o.y, cylinder->cylinder.o.z);
**	printf("ray->hit_normal: %lf, %lf, %lf\n",
**		ray->hit_normal.x, ray->hit_normal.y, ray->hit_normal.z);
**ajouter gestion lumiere au sein d'un objet en comparant si t < 0 et t2 > 0
*/

static BOOL	find_delta(t_ray *ray, t_obj *cylinder, t_inter *inter)
{
	t_vector	ray_cyl_o;
	double		scalar;
	t_cyl		cyl;

	ray_cyl_o = sub_vectors(&(ray->o), &(cylinder->o));
	scalar = get_scalar_product(&(ray->dir), &(cylinder->normal));
	cyl.v = multiply_vector(&(cylinder->normal), scalar);
	cyl.v = sub_vectors(&(ray->dir), &(cyl.v));
	scalar = get_scalar_product(&ray_cyl_o, &(cylinder->normal));
	cyl.u = multiply_vector(&(cylinder->normal), scalar);
	cyl.u = sub_vectors(&ray_cyl_o, &(cyl.u));
	cyl.a = get_norme(&(cyl.v));
	cyl.b = 2.0 * get_scalar_product(&(cyl.v), &(cyl.u));
	cyl.c = get_norme(&cyl.u) - (cylinder->radius * cylinder->radius);
	cyl.delta = cyl.b * cyl.b - 4 * cyl.a * cyl.c;
	if (cyl.delta < 0)
		return (FALSE);
	inter->t1 = ((-cyl.b) - sqrt(cyl.delta)) / (2 * cyl.a);
	inter->t2 = ((-cyl.b) + sqrt(cyl.delta)) / (2 * cyl.a);
	if (inter->t1 >= inter->t2)
		printf("WHAT?!\n");
	if ((inter->t1 < 0 && inter->t2 < 0)
		|| (inter->t1 != inter->t1 && inter->t2 != inter->t2))
		return (FALSE);
	return (TRUE);
}

/*
**a = ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y;
**b = 2 * (ray->o.x * ray->dir.x + ray->o.y * ray->dir.y
**	- ray->dir.x * cylinder->o.x - ray->dir.y * cylinder->o.y);
**c = ray->o.x * ray->o.x + ray->o.y * ray->o.y + cylinder->o.x * cylinder->o.x
**	+ cylinder->o.y * cylinder->o.y - cylinder->radius * cylinder->radius
**	- 2 * (ray->o.x * ray->o.x + ray->o.y * cylinder->o.y);
**delta = b * b - 4 * a * c;
**t3 = ((-b) - sqrt(delta)) / (2 * a);
**t4 = ((-b) + sqrt(delta)) / (2 * a);
**printf("t3: %lf   t4: %lf\n", t3, t4);
*/

BOOL	is_intersect_cylinder(t_ray *ray, t_obj *cylinder, t_inter *inter)
{
	t_vector	ray_cyl_o;
	t_point		hit_point;

	if (!find_delta(ray, cylinder, inter))
		return (FALSE);
	ray_cyl_o = sub_vectors(&(cylinder->o), &(ray->o));
	hit_point = multiply_vector(&(ray->dir), inter->t1);
	hit_point = add_vectors(&(ray->o), &hit_point);
	hit_point = sub_vectors(&(hit_point), &(cylinder->o));
	inter->dist = get_scalar_product(&(cylinder->normal), &(hit_point));
	inter->hit_inside = FALSE;
	if (inter->t1 > 0 && inter->t1 == inter->t1
		&& inter->dist > 0 && inter->dist < cylinder->h)
		return (TRUE);
	hit_point = multiply_vector(&(ray->dir), inter->t2);
	hit_point = add_vectors(&(ray->o), &hit_point);
	hit_point = sub_vectors(&(hit_point), &(cylinder->o));
	inter->dist = get_scalar_product(&(cylinder->normal), &(hit_point));
	if (!(inter->t2 > 0 && inter->t2 == inter->t2
			&& inter->dist > 0 && inter->dist < cylinder->h))
		return (FALSE);
	inter->hit_inside = TRUE;
	inter->t1 = inter->t2;
	return (TRUE);
}
