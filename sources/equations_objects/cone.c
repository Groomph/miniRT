/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:24:18 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/19 16:42:43 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void		set_cone_normal(t_ray *ray, t_obj *cone)
{
	t_vector	hit_from_cam;
	t_vector	center;
	double		coss;

	hit_from_cam = multiply_vector(&(ray->dir), ray->t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	hit_from_cam = sub_vectors(&(ray->hit), &(cone->o));
	set_normalized(&hit_from_cam);
	center = get_vector_product(&(cone->normal), &hit_from_cam);
	set_normalized(&center);
	ray->hit_normal = get_vector_product(&center, &hit_from_cam);
	set_normalized(&(ray->hit_normal));
	coss = get_scalar_product(&(ray->hit_normal), &(ray->dir));
	if (coss > 0.0)
		ray->hit_normal = multiply_vector(&(ray->hit_normal), -1);
}

static void	find_delta(t_ray *ray, t_obj *cone, t_cyl *co)
{
	double		coss;
	double		scalar;
	double		scalar2;
	t_vector	ray_con_o;

	coss = cos(cone->radius) * cos(cone->radius);
	scalar = get_scalar_product(&(ray->dir), &(cone->normal));
	co->a = scalar * scalar - coss;
	ray_con_o = sub_vectors(&(ray->o), &(cone->o));
	scalar2 = get_scalar_product(&ray_con_o, &(cone->normal));
	co->b = scalar * scalar2;
	scalar = get_scalar_product(&(ray->dir), &ray_con_o);
	scalar *= coss;
	co->b = 2 * (co->b - scalar);
	co->c = get_norme(&ray_con_o) * coss;
	co->c = scalar2 * scalar2 - co->c;
	co->delta = co->b * co->b - 4 * co->a * co->c;
}

static BOOL	find_intersections(t_ray *ray, t_obj *cone, t_inter *inter)
{
	t_cyl		co;

	find_delta(ray, cone, &co);
	if (co.delta < 0)
		return (FALSE);
	inter->t1 = ((-co.b) - sqrt(co.delta)) / (2 * co.a);
	inter->t2 = ((-co.b) + sqrt(co.delta)) / (2 * co.a);
	if (inter->t1 > inter->t2)
	{
		co.a = inter->t1;
		inter->t1 = inter->t2;
		inter->t2 = co.a;
	}
	if ((inter->t1 < 0 && inter->t2 < 0)
			|| (inter->t1 != inter->t1 && inter->t2 != inter->t2))
		return (FALSE);
	inter->hit_inside = FALSE;
	return (TRUE);
}

BOOL		is_intersect_cone(t_ray *ray, t_obj *cone, t_inter *inter)
{
	t_point	hit_point;
	double	scalar;

	if (!find_intersections(ray, cone, inter))
		return (FALSE);
	hit_point = multiply_vector(&(ray->dir), inter->t1);
	hit_point = add_vectors(&(ray->o), &hit_point);
	hit_point = sub_vectors(&hit_point, &(cone->o));
	inter->dist = sqrt(get_norme(&hit_point));
	scalar = get_scalar_product(&hit_point, &(cone->normal));
	if (inter->t1 > 0 && inter->t1 == inter->t1
			&& inter->dist > 0 && inter->dist < cone->h && scalar > 0)
		return (TRUE);
	hit_point = multiply_vector(&(ray->dir), inter->t2);
	hit_point = add_vectors(&(ray->o), &hit_point);
	hit_point = sub_vectors(&hit_point, &(cone->o));
	inter->dist = sqrt(get_norme(&hit_point));
	scalar = get_scalar_product(&hit_point, &(cone->normal));
	if (!(inter->t2 > 0 && inter->t2 == inter->t2
			&& inter->dist > 0 && inter->dist < cone->h && scalar > 0))
		return (FALSE);
	inter->hit_inside = TRUE;
	inter->t1 = inter->t2;
	return (TRUE);
}
