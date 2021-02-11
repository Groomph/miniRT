/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:24:18 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/10 19:01:32 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>

void		set_triangle_normal(t_ray *ray, t_obj *triangle)
{
	double		cos;
	t_vector	normal;
	t_point		hit_from_cam;

	hit_from_cam = multiply_vector(&(ray->dir), ray->t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	cos = get_scalar_product(&(triangle->normal), &(ray->dir));
	if (cos > 0.0)
	{
		ray->hit_normal = multiply_vector(&(triangle->normal), -1);
	}
	else
	{
		ray->hit_normal = triangle->normal;
	}
	set_normalized(&(ray->hit_normal));
}

/*
**	printf("ray->hit: %lf, %lf, %lf\n",
**					ray->hit.x, ray->hit.y, ray->hit.z);
**	printf("triangle->o: %lf, %lf, %lf\n",
**		triangle->triangle.o.x, triangle->triangle.o.y, triangle->triangle.o.z);
**	printf("ray->hit_normal: %lf, %lf, %lf\n",
**		ray->hit_normal.x, ray->hit_normal.y, ray->hit_normal.z);
**ajouter gestion lumiere au sein d'un objet en comparant si t < 0 et t2 > 0
*/

static BOOL	find_t(t_inter *inter, t_tri *tri)
{
	double	t;

	t = tri->cos * get_scalar_product(&(tri->edge2), &(tri->q));
	if (t < 0.0)
		return (FALSE);
	inter->t1 = t;
	inter->hit_inside = FALSE;
	return (TRUE);
}

BOOL		is_intersect_triangle(t_ray *ray, t_obj *triangle, t_inter *inter)
{
	t_tri		tri;
	t_vector	tri_ray_o;
	double		u;
	double		v;

	tri.edge1 = sub_vectors(&(triangle->o2), &(triangle->o));
	tri.edge2 = sub_vectors(&(triangle->o3), &(triangle->o));
	tri.h = get_vector_product(&(ray->dir), &(tri.edge2));
	tri.cos = get_scalar_product(&(tri.edge1), &(tri.h));
	if (tri.cos > -EPSILON && tri.cos < EPSILON)
		return (FALSE);
	tri.cos = 1.0 / tri.cos;
	tri_ray_o = sub_vectors(&(ray->o), &(triangle->o));
	u = tri.cos * get_scalar_product(&tri_ray_o, &(tri.h));
	if (u < 0.0 || u > 1.0)
		return (FALSE);
	tri.q = get_vector_product(&tri_ray_o, &(tri.edge1));
	v = tri.cos * get_scalar_product(&(ray->dir), &(tri.q));
	if (v < 0.0 || u + v > 1.0)
		return (FALSE);
	return (find_t(inter, &tri));
}
