/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 07:50:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/30 12:28:13 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

static BOOL	is_illuminated(t_scene *scene, t_ray *light_ray, t_ray *ray)
{
	t_obj	*obj;
	t_inter	temp;
	BOOL	hit;

	obj = scene->object;
	while (obj)
	{
		if (obj != ray->nearest_object)
		{
			if (obj->inter_f(light_ray, obj, &temp)
						&& temp.t1 < light_ray->t)
				return (FALSE);
		}
		else if (ray->hit_inside)
		{
			hit = obj->inter_f(light_ray, obj, &temp);
			if ((hit && temp.hit_inside && temp.t1 < light_ray->t)
				|| (hit && !temp.hit_inside && temp.t2 < light_ray->t))
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

void		apply_light(t_scene *scene, t_light *light, t_ray *ray)
{
	t_ray		light_ray;
	double		cos;
	double		normed_squarred;
	t_vector	temp;

	ray->nearest_object->normal_f(ray, ray->nearest_object);
	light_ray.dir = sub_vectors(&(light->o), &(ray->hit));
	normed_squarred = get_norme(&light_ray.dir);
	set_normalized(&(light_ray.dir));
	cos = get_scalar_product(&(light_ray.dir), &(ray->hit_normal));
	if (cos <= 0.0)
		return ;
	light_ray.o = ray->hit;
	light_ray.t = sqrt(normed_squarred);
	if (!(is_illuminated(scene, &light_ray, ray)))
		return ;
	cos *= (50 / normed_squarred);
	ray->color.x += cos * (ray->nearest_object->color.x
				* (light->color.x / 255) * light->intensity);
	ray->color.y += cos * (ray->nearest_object->color.y
				* (light->color.y / 255) * light->intensity);
	ray->color.z += cos * (ray->nearest_object->color.z
				* (light->color.z / 255) * light->intensity);
}

/*
** 	ray->color.x +=
**		cos * (scene->ambient_light.x / 255 * scene->ambient_intensity)
**		* (ray->nearest_object->color.x	* (light->color.x / 255)
							* light->intensity);
**	ray->color.y +=
**		cos * (scene->ambient_light.y / 255 * scene->ambient_intensity)
**		* (ray->nearest_object->color.y
**			* (light->color.y / 255) * light->intensity);
**	ray->color.z +=
**		cos * (scene->ambient_light.z / 255 * scene->ambient_intensity)
**			* (ray->nearest_object->color.z
**			* (light->color.z / 255) * light->intensity);
*/

/*
**	ray->color_final.y += ray->color_object.y * light_intensity
**							* light->color.y / 255;
**	ray->color_final.z += ray->color_object.z * light_intensity
**							* light->color.z / 255;
**	printf("        %.1lf,%.1lf,%.1lf\n\n", light->data.light.o.x,
**						light->data.light.o.y,
**						light->data.light.o.z);
**
**	double		light_intensity;
**	light_intensity = 100 * light->data.light.intensity;
**	light_intensity *= cos;
**	light_intensity /= get_norme(&rev_lightray);
**
**	temp = multiply_vector(&(ray->hit_normal), 0.003);
**	light_ray.o = add_vectors(&(ray->hit), &temp);
*/
