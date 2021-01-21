/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:13:44 by romain            #+#    #+#             */
/*   Updated: 2021/01/21 05:40:07 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>

void		set_hit_normale(t_ray *ray, t_sphere *sphere)
{
	double	t;
	t_point	hit_from_cam;

	if (ray->t[0] >= 0)
		t = ray->t[0];
	else
	{
		t = ray->t[1];
		ray->t[1] = ray->t[0];
		ray->t[0] = t;
	}
	hit_from_cam = multiply_vector(&(ray->dir), t);
	ray->hit = add_vectors(&(ray->o), &hit_from_cam);
	ray->hit_normale = sub_vectors(&(ray->hit), &(sphere->o));
	set_normalized(&(ray->hit_normale));
}

/*
**ajouter gestion de la lumiere au sein d'un objet en comparant si t < 0 et t2 > 0
*/

BOOL		is_intercept_sphere(t_ray *ray, t_data *data)
{
	t_vector	ray_sph_o;
	double		b;
	double		c;
	double		delta;

	ray_sph_o = sub_vectors(&(ray->o), &(data->sphere.o));
	b = get_scalar_product(&ray_sph_o, &(ray->dir));
	c = get_norme(&ray_sph_o) - data->sphere.radius * data->sphere.radius;
	delta = (b * b) - c;
	if (delta < 0.0)
		return (FALSE);
	delta = sqrt(delta);
	ray->t[0] = (-b - delta);
	if (ray->t[0] < 0 || ray->t[0] > ray->max_t)
	{
		ray->t[1] = -b + delta;
		if (ray->t[1] < 0 || ray->t[1] > ray->max_t)
			return (FALSE);
//		write(1, "do we enter?\n", 14);
	}
	set_hit_normale(ray, &(data->sphere));
	return (TRUE);
}

/*
**double	a;
**a = get_norme(&(ray->dir));
**delta = (b * b) - (a * c);
*/

static int	parse_sphere(t_obj *sphere, char *format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(sphere->data.sphere.o), format, &i)
		|| !double_microparser(&(sphere->data.sphere.radius), format, &i)
		|| sphere->data.sphere.radius <= 0
		|| !color_microparser(&(sphere->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	sphere->f = is_intercept_sphere;
	printf("        %.1lf,%.1lf,%.1lf      ", sphere->data.sphere.o.x,
						sphere->data.sphere.o.y,
						sphere->data.sphere.o.z);
	printf("%.2lf    ", sphere->data.sphere.radius);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n",
	sphere->color.other, sphere->color.x, sphere->color.y, sphere->color.z);
	return (TRUE);
}

int			add_sphere(t_scene *scene, char *format)
{
	t_obj		*sphere;
	t_list		*temp_list;

	sphere = malloc(sizeof(t_obj));
	if (!sphere)
		return (FALSE);
	temp_list = list_new(sphere);
	if (!temp_list)
	{
		free(sphere);
		return (FALSE);
	}
	list_add_front(&(scene->object), temp_list);
	if (!parse_sphere(sphere, format))
		return (-1);
	return (TRUE);
}
