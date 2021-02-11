/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:41:07 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/10 23:50:49 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

BOOL	find_nearest_object(t_scene *scene, t_ray *ray)
{
	t_obj	*temp_obj;
	int		check;
	t_inter	inter;

	temp_obj = scene->object;
	check = 0;
	while (temp_obj)
	{
		if (temp_obj->inter_f(ray, temp_obj, &inter))
		{
			if (ray->t > inter.t1)
			{
				ray->t = inter.t1;
				ray->hit_inside = inter.hit_inside;
				ray->nearest_object = temp_obj;
				ray->dist = inter.dist;
				check++;
			}
		}
		temp_obj = temp_obj->next;
	}
	if (check)
		return (TRUE);
	return (FALSE);
}

void		reflect_ray(t_scene *scene, t_ray *ray, int i)
{
	t_vector	temp;
	double		cos;

	ray->nearest_object->normal_f(ray, ray->nearest_object);
	temp = multiply_vector(&(ray->hit_normal), EPSILON);
	ray->o = add_vectors(&(ray->hit), &temp);
	ray->t = 1000000;
	cos = 2.0 * get_scalar_product(&(ray->dir), &(ray->hit_normal));
	temp = multiply_vector(&(ray->hit_normal), cos);
	ray->dir = sub_vectors(&(ray->dir), &temp);
	set_normalized(&(ray->dir));
	path_tracer(scene, ray, i + 1);
}

void		path_tracer(t_scene *scene, t_ray *ray, int i)
{
	t_light	*temp_light;

	if (find_nearest_object(scene, ray))
	{
		if (ray->nearest_object->specular && i < scene->cam->recursivity)
			return (reflect_ray(scene, ray, i));
		apply_ambient_light(scene, ray);
		temp_light = scene->light;
		while (temp_light)
		{
			apply_light(scene, temp_light, ray);
			temp_light = temp_light->next;
		}
	}
}
