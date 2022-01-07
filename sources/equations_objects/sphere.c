/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:24:18 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 15:02:40 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>

void	set_sphere_normal(t_ray *ray, t_obj *sphere)
{
	t_point	hit_from_cam;

	hit_from_cam = multiply_vector(&(ray->dir), ray->t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	if (ray->hit_inside)
	{
		ray->hit_normal = sub_vectors(&(sphere->o), &(ray->hit));
	}
	else
	{
		ray->hit_normal = sub_vectors(&(ray->hit), &(sphere->o));
	}
	set_normalized(&(ray->hit_normal));
}

/*
**	printf("ray->hit: %lf, %lf, %lf\n",
**					ray->hit.x, ray->hit.y, ray->hit.z);
**	printf("sphere->o: %lf, %lf, %lf\n",
**		sphere->sphere.o.x, sphere->sphere.o.y, sphere->sphere.o.z);
**	printf("ray->hit_normal: %lf, %lf, %lf\n",
**		ray->hit_normal.x, ray->hit_normal.y, ray->hit_normal.z);
**ajouter gestion lumiere au sein d'un objet en comparant si t < 0 et t2 > 0
*/

static double	find_delta(t_ray *ray, t_obj *sphere, double *b)
{
	t_vector	ray_sph_o;
	double		c;

	ray_sph_o = sub_vectors(&(ray->o), &(sphere->o));
	*b = get_scalar_product(&ray_sph_o, &(ray->dir));
	c = get_norme(&ray_sph_o) - sphere->radius * sphere->radius;
	return ((*b * *b) - c);
}

BOOL	is_intersect_sphere(t_ray *ray, t_obj *sphere, t_inter *inter)
{
	double		delta;
	double		b;
	double		t1;
	double		t2;

	delta = find_delta(ray, sphere, &b);
	if (delta <= 0.0)
		return (FALSE);
	delta = sqrt(delta);
	t1 = (-b) - delta;
	t2 = (-b) + delta;
	if (t1 < 0.0)
	{
		if (t2 < 0.0)
			return (FALSE);
		inter->t1 = t2;
		inter->t2 = t1;
		inter->hit_inside = TRUE;
		return (TRUE);
	}
	inter->t1 = t1;
	inter->t2 = t2;
	inter->hit_inside = FALSE;
	return (TRUE);
}

/*
**BOOL		is_intercept_sphere(t_ray *ray, t_obj *sphere, t_inter *inter)
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
**	ray_sph_o = sub_vectors(&(ray->o), &(sphere->o));
**	printf("ray_sph_o: %lf %lf %lf\n", ray_sph_o.x, ray_sph_o.y, ray_sph_o.z);
**	b = 2 * get_scalar_product(&ray_sph_o, &(ray->dir));
**	printf("b: %lf\n", b);
**	c = get_norme(&ray_sph_o) - sphere->radius * sphere->radius;
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
**		write(1, "do we enter sphere intersection?\n", 13);
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
