/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:24:18 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 15:02:56 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void	set_square_normal(t_ray *ray, t_obj *square)
{
	double		cos;
	t_point		hit_from_cam;

	hit_from_cam = multiply_vector(&(ray->dir), ray->t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	cos = get_scalar_product(&(square->normal), &(ray->dir));
	if (cos > 0.0)
	{
		ray->hit_normal = multiply_vector(&(square->normal), -1);
	}
	else
	{
		ray->hit_normal = square->normal;
	}
	set_normalized(&(ray->hit_normal));
}

/*
** 	if (ray->hit_normal.x == -0.0)
**		ray->hit_normal.x = 0.0;
**	if (ray->hit_normal.y == -0.0)
**		ray->hit_normal.y = 0.0;
**	if (ray->hit_normal.z == -0.0)
**		ray->hit_normal.z = 0.0;
**	printf("ray->hit_normal: %lf, %lf, %lf\n",
**		ray->hit_normal.x, ray->hit_normal.y, ray->hit_normal.z);
*/

/*
**	printf("ray->hit: %lf, %lf, %lf\n",
**					ray->hit.x, ray->hit.y, ray->hit.z);
**	printf("square->o: %lf, %lf, %lf\n",
**		square->square.o.x, square->square.o.y, square->square.o.z);
**	printf("ray->hit_normal: %lf, %lf, %lf\n",
**		ray->hit_normal.x, ray->hit_normal.y, ray->hit_normal.z);
**ajouter gestion lumiere au sein d'un objet en comparant si t < 0 et t2 > 0
*/

/*
**BOOL		is_intercept_square2(t_ray *ray, t_obj *square, t_inter *inter)
**{
**	t_inter		inter2;
**	t_vector	p;
**	t_vector	floor;
**	t_vector	half;
**	t_vector	op;
**	double	coss;
**	double	scalar;
**	double	limit;
**
**	if (!is_intercept_plane(ray, square, &inter2))
**		return (FALSE);
**	p = multiply_vector(&(ray->dir), inter2.t1);
**	p = add_vectors(&p, &(ray->o));
**	if (square->normal.y == 1.0 || square->normal.y == -1.0)
**		floor = get_vector(0.0, 1.0, 0.0, 0.0);
**	else
**		floor = get_vector(0.0, 0.0, 1.0, 0.0);
**	half = get_vector_product(&(square->normal), &floor);
**	op = sub_vectors(&p, &(square->o));
**
**
**	scalar = get_scalar_product(&half, &op);
**	scalar /= (sqrt(get_norme(&half)) * sqrt(get_norme(&op)));
**	if (scalar < 0.0)
**		coss = -scalar;
**	else
**		coss = scalar;
**	if (coss < 0.707106781)//sqrt(2) / 2)
**		coss = cos(PI_2 - acos(coss)); //acos == cos-1
**	limit = (square->radius / 2) / coss;
**	if (sqrt(get_norme(&op)) > limit)
**		return (FALSE);
**	inter->t1 = inter2.t1;
**	inter->hit_inside = FALSE;
**	return (TRUE);
**}
*/

BOOL	is_intersect_square(t_ray *ray, t_obj *square, t_inter *inter)
{
	t_inter		inter2;
	t_vector	hit_point;
	double		cos1;
	double		cos2;
	t_vector	ap;

	if (!is_intersect_plane(ray, square, &inter2))
		return (FALSE);
	hit_point = multiply_vector(&(ray->dir), inter2.t1);
	hit_point = add_vectors(&hit_point, &(ray->o));
	ap = sub_vectors(&hit_point, &(square->a));
	cos1 = get_scalar_product(&ap, &(square->ab));
	cos2 = get_scalar_product(&ap, &(square->ad));
	cos1 /= get_norme(&(square->ab));
	cos2 /= get_norme(&(square->ad));
	if (!(cos1 >= 0.0 && cos1 <= 1.0 && cos2 >= 0.0 && cos2 <= 1.0))
		return (FALSE);
	inter->t1 = inter2.t1;
	inter->hit_inside = FALSE;
	return (TRUE);
}
