/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 03:51:58 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 14:57:50 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

static BOOL	is_intersect_box(t_sky_box *square, t_ray *ray)
{
	t_vector	hit_point;
	double		cos1;
	double		cos2;
	t_vector	ap;
	double		t;

	cos1 = get_scalar_product(&(square->normal), &(ray->dir));
	t = get_scalar_product(&(square->normal), (&square->o)) / cos1;
	if (t < 0.0)
		return (FALSE);
	hit_point = multiply_vector(&(ray->dir), t);
	ap = sub_vectors(&hit_point, &(square->a));
	cos1 = get_scalar_product(&ap, &(square->ab));
	cos2 = get_scalar_product(&ap, &(square->ad));
	cos1 /= get_norme(&(square->ab));
	cos2 /= get_norme(&(square->ad));
	if (!(cos1 >= 0.0 && cos1 <= 1.0 && cos2 >= 0.0 && cos2 <= 1.0))
		return (FALSE);
	ray->hit = hit_point;
	return (TRUE);
}

static int	find_pixel(t_ray *ray, int i)
{
	int	w;
	int	h;

	w = 0;
	h = -1 * ray->hit.y;
	if (i <= 1)
	{
		w = ray->hit.x;
		h = ray->hit.z;
	}
	else if (i == 2)
		w = ray->hit.x;
	else if (i == 3)
		w = -1 * ray->hit.x;
	else if (i == 4)
		w = ray->hit.z;
	else if (i == 5)
		w = -1 * ray->hit.z;
	return ((512 + h) * 1024 + (w + 512));
}

void	skybox_intersect(t_scene *scene, t_ray *ray)
{
	int	i;
	int	pixel;

	i = 0;
	while (i < 6)
	{
		if (is_intersect_box(&(scene->skybox[i]), ray))
		{
			pixel = find_pixel(ray, i);
			pixel = scene->skybox[i].addr[pixel];
			ray->color.x = (pixel >> 16) & 0xff;
			ray->color.y = (pixel >> 8) & 0xff;
			ray->color.z = pixel & 0xff;
			return ;
		}
		i++;
	}
	printf("ERROR\n");
}
