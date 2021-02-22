/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:41:07 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/22 19:44:54 by rsanchez         ###   ########.fr       */
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

	temp = multiply_vector(&(ray->hit_normal), EPSILON);
	ray->o = add_vectors(&(ray->hit), &temp);
	ray->t = 1000000;
	cos = 2.0 * get_scalar_product(&(ray->dir), &(ray->hit_normal));
	temp = multiply_vector(&(ray->hit_normal), cos);
	ray->dir = sub_vectors(&(ray->dir), &temp);
	set_normalized(&(ray->dir));
	path_tracer(scene, ray, i + 1);
}

void		set_disruption(t_ray *ray)
{
	ray->temp_color = ray->nearest_object->color;
	if (ray->nearest_object->rainbow)
		rainbow(ray, ray->nearest_object->type);
	if (ray->nearest_object->check_board)
		check_board(ray);
	if (ray->nearest_object->perlin == TRUE)
		perlin(ray->hit, &(ray->temp_color));
	if (ray->nearest_object->marbre == TRUE)
		marbre(ray->hit, &(ray->temp_color));
	if (ray->nearest_object->liana == TRUE)
		liana(ray->hit, &(ray->temp_color));
	if (ray->nearest_object->water == TRUE)
		water(&(ray->hit), &(ray->hit_normal));
	if (ray->nearest_object->wave == TRUE)
		wave(&(ray->hit), &(ray->hit_normal));
}

void		path_tracer(t_scene *scene, t_ray *ray, int i)
{
	t_light	*temp_light;

	if (find_nearest_object(scene, ray))
	{
		ray->nearest_object->normal_f(ray, ray->nearest_object);
		if (ray->nearest_object->specular && i < scene->cam->recursivity)
			return (reflect_ray(scene, ray, i));
		set_disruption(ray);
		apply_light_effects(ray, &(scene->ambient), 1.0);
		temp_light = scene->light;
		while (temp_light)
		{
			apply_light(scene, ray, temp_light);
			temp_light = temp_light->next;
		}
	}
	else if (scene->box == TRUE)
		skybox_intersect(scene, ray);
}
