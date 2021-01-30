/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:41:07 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/30 12:17:55 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

BOOL	find_nearest_object(t_scene *scene, t_ray *ray, void *ignore)
{
	t_obj	*temp_obj;
	int		check;
	t_inter	inter;

	temp_obj = scene->object;
	check = 0;
	while (temp_obj)
	{
		if (temp_obj != ignore
				&& temp_obj->inter_f(ray, temp_obj, &inter))
		{
			if (ray->t > inter.t1)
			{
				ray->t = inter.t1;
				ray->hit_inside = inter.hit_inside;
				ray->nearest_object = temp_obj;
				check++;
			}
		}
		temp_obj = temp_obj->next;
	}
	if (check)
		return (TRUE);
	return (FALSE);
}

/*
**BOOL		quick_path_tracer(t_scene *scene, t_ray *ray, double max_t)
**{
**	t_list	*temp_list;
**	t_obj	*temp_obj;
**
**	temp_list = scene->object;
**	ray->nearest_object = NULL;
**	ray->max_t = 1000;
**	ray->t = 0;
**	while (temp_list)
**	{
**		temp_obj = temp_list->object;
**		if (temp_obj->inter_f(ray, &(temp_obj->data)))
**			return (FALSE);
**		temp_list = temp_list->next;
**	}
**	return (TRUE);
**}
*/

int		path_tracer(t_scene *scene, t_ray *ray, void *ignore, int i)
{
	t_light	*temp_light;
	t_vector	temp;
	double		cos;

	ray->t = 1000000;
	ray->color = get_vector(0, 0, 0, 0);
	if (find_nearest_object(scene, ray, ignore))
	{
		if (ray->nearest_object->radius < 1.0 && i < 2)
		{
			ray->nearest_object->normal_f(ray, ray->nearest_object);
			temp = multiply_vector(&(ray->hit_normal), 0.001);
			ray->o = add_vectors(&(ray->hit), &temp);
			ray->t = 1000000;
			cos = 2.0 * get_scalar_product(&(ray->dir), &(ray->hit_normal));
			temp = multiply_vector(&(ray->hit_normal), cos);
			ray->dir = sub_vectors(&(ray->dir), &temp);
			set_normalized(&(ray->dir));
			return (path_tracer(scene, ray, NULL, i + 1));
		}
		apply_ambient_light(scene, ray);
		temp_light = scene->light;
		while (temp_light)
		{
			apply_light(scene, temp_light, ray);
			temp_light = temp_light->next;
		}
	}
	return (fuse_vector(&(ray->color)));
}
