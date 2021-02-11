/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 07:50:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/10 20:38:20 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

static BOOL	is_illuminated(t_scene *scene, t_ray *light_ray,
						t_ray *ray, t_ray *temp_light)
{
	t_obj	*obj;
	t_inter	temp;

	obj = scene->object;
	while (obj)
	{
		if (obj != ray->nearest_object)
		{
			if (obj->inter_f(light_ray, obj, &temp)
					&& temp.t1 < light_ray->t)
				return (FALSE);
		}
		else// if (ray->hit_inside == TRUE)
		{
			if (obj->inter_f(temp_light, obj, &temp)
					&& temp.t1 < temp_light->t)
				return (FALSE);
		}
		obj = obj->next;
	}
	return (TRUE);
}

void		apply_ambient_light(t_scene *scene, t_ray *ray)
{
	ray->color.x = ray->nearest_object->color.x * scene->ambient_intensity
						* (scene->ambient_light.x / 255);
	ray->color.y = ray->nearest_object->color.y * scene->ambient_intensity
						* (scene->ambient_light.y / 255);
	ray->color.z = ray->nearest_object->color.z * scene->ambient_intensity
						* (scene->ambient_light.z / 255);
}

static void		apply_light_effects(t_ray *ray, t_light *light, double cos)
{
	if (cos < 0.0)
		cos *= -1.0;
	ray->color.x += cos * (ray->nearest_object->color.x
				* (light->color.x / 255) * light->intensity);
	ray->color.y += cos * (ray->nearest_object->color.y
				* (light->color.y / 255) * light->intensity);
	ray->color.z += cos * (ray->nearest_object->color.z
				* (light->color.z / 255) * light->intensity);
}

void		apply_light(t_scene *scene, t_light *light, t_ray *ray)
{
	t_ray		light_ray;
	t_ray		temp_light;
	double		cos;
	double		normed_squarred;
	t_vector	temp;

	ray->nearest_object->normal_f(ray, ray->nearest_object);
	light_ray.o = ray->hit;
	light_ray.dir = sub_vectors(&(light->o), &(ray->hit));
	normed_squarred = set_normalized(&(light_ray.dir));
	light_ray.t = sqrt(normed_squarred);
	cos = get_scalar_product(&(light_ray.dir), &(ray->hit_normal));
	if (cos < EPSILON && cos > -EPSILON)
		return ;
	if (cos < EPSILON && (ray->nearest_object->type == SPHERE
			|| ray->nearest_object->type == CYLINDER))
		return ;
	temp_light.o = multiply_vector(&(ray->hit_normal), EPSILON);
	temp_light.o = add_vectors(&(temp_light.o), &(ray->hit));
	temp_light.dir = sub_vectors(&(light->o), &(temp_light.o));
	temp_light.t = sqrt(set_normalized(&(temp_light.dir)));
	if (!is_illuminated(scene, &light_ray, ray, &temp_light))
		return ;
	apply_light_effects(ray, light, cos * (50 / normed_squarred));
}
