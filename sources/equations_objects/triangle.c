/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:24:18 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/02 13:35:25 by rsanchez         ###   ########.fr       */
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
	if (t <= EPSILON)
		return (FALSE);
	inter->t1 = t;
	inter->hit_inside = FALSE;
	return (TRUE);
}

BOOL		is_intercept_triangle(t_ray *ray, t_obj *triangle, t_inter *inter)
{
	t_tri		tri;
	t_vector	ray_tri_o;
	double		area_u;

	tri.edge1 = sub_vectors(&(triangle->o2), &(triangle->o));
	tri.edge2 = sub_vectors(&(triangle->o3), &(triangle->o));
	tri.h = get_vector_product(&(ray->dir), &(tri.edge2));
	tri.cos = get_scalar_product(&(tri.edge1), &(tri.h));
	if (tri.cos > -EPSILON && tri.cos < EPSILON)
		return (FALSE);
	tri.cos = 1.0 / tri.cos;
	ray_tri_o = sub_vectors(&(ray->o), &(triangle->o));
	area_u = tri.cos * get_scalar_product(&ray_tri_o, &(tri.h));
	if (area_u < 0.0 || area_u > 1.0)
		return (FALSE);
	tri.q = get_vector_product(&ray_tri_o, &(tri.edge1));
	tri.v = tri.cos * get_scalar_product(&(ray->dir), &(tri.q));
	if (tri.v < 0.0 || area_u + tri.v > 1.0)
		return (FALSE);
	return (find_t(inter, &tri));
}

/*
**BOOL		is_intercept_triangle(t_ray *ray, t_obj *triangle, t_inter *inter)
**{
**	t_vector	ray_sph_o;
**	double		a;
**	double		b;
**	double		c;
**	double		delta;
**	double		t1;
**	double		t2;
**
**	a = get_norme(&(ray->dir));
** 	printf("a: %lf\n", a);
**	ray_sph_o = sub_vectors(&(ray->o), &(triangle->o));
**	printf("ray_sph_o: %lf %lf %lf\n", ray_sph_o.x, ray_sph_o.y, ray_sph_o.z);
**	b = 2 * get_scalar_product(&ray_sph_o, &(ray->dir));
**	printf("b: %lf\n", b);
**	c = get_norme(&ray_sph_o) - triangle->radius * triangle->radius;
**	printf("c: %lf\n", c);
**	delta = (b * b) - 4 * a * c;
**	printf("delta: %lf\n", delta);
**	if (delta < 0.0)
**		return (FALSE);
**	delta = sqrt(delta);
**	t1 = ((-b) - sqrt(delta)) / (2 * a);
**	t2 = ((-b) + sqrt(delta)) / (2 * a);
**	printf("t1: %lf\n", t);
**	if (t1 < 0.0 || t1 >= 100 || t1 >= ray->t || t1 == INFINITY)
**	{
**		printf("t2: %lf\n", t);
**		if (t2 < 0.0 || t2 >= 100 || t2 >= ray->t || t2 == INFINITY)
**			return (FALSE);
**		write(1, "do we enter triangle intersection?\n", 13);
**		inter->t1 = t2;
**		inter->t2 = t1;
**		inter->hit_inside = TRUE;
**		return (TRUE);
**	}
**	inter->t1 = t1;
**	inter->t2 = t2;
**	inter->hit_inside = FALSE;
**	return (TRUE);
**}
*/

/*
**double	a;
**a = get_norme(&(ray->dir));
**delta = (b * b) - (a * c);
*/
