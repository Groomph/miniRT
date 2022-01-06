/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 07:50:54 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/06 19:33:44 by rsanchez         ###   ########.fr       */
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
		else
		{
			if (obj->inter_f(temp_light, obj, &temp)
				&& temp.t1 < temp_light->t)
				return (FALSE);
		}
		obj = obj->next;
	}
	return (TRUE);
}

/*
**		else// if (ray->hit_inside == TRUE)
*/

/*
**void		apply_ambient_light(t_scene *scene, t_ray *ray)
**{
**	ray->color.x = ray->nearest_object->color.x * scene->ambient_intensity
**						* (scene->ambient_light.x / 255);
**	ray->color.y = ray->nearest_object->color.y * scene->ambient_intensity
**						* (scene->ambient_light.y / 255);
**	ray->color.z = ray->nearest_object->color.z * scene->ambient_intensity
**						* (scene->ambient_light.z / 255);
**}
*/

void	apply_light_effects(t_ray *ray, t_light *light, double cos)
{
	if (cos < 0.0)
		cos *= -1.0;
	ray->color.x += cos * (ray->temp_color.x * light->intensity
			* (light->color.x / 255));
	ray->color.y += cos * (ray->temp_color.y * light->intensity
			* (light->color.y / 255));
	ray->color.z += cos * (ray->temp_color.z * light->intensity
			* (light->color.z / 255));
}

static double	set_light_ray(t_ray *ray, t_light *light,
						t_ray *light_ray, double *norme)
{
	light_ray->o = ray->hit;
	if (light->parallel)
	{
		light_ray->dir = multiply_vector(&(light->o), -1.0);
		*norme = 50;
		light_ray->t = 1000000;
	}
	else
	{
		light_ray->dir = sub_vectors(&(light->o), &(ray->hit));
		*norme = set_normalized(&(light_ray->dir));
		light_ray->t = sqrt(*norme);
	}
	return (get_scalar_product(&(light_ray->dir), &(ray->hit_normal)));
}

static void	set_temp_light_ray(t_ray *ray, t_light *light, t_ray *light_ray)
{
	light_ray->o = multiply_vector(&(ray->hit_normal), EPSILON);
	light_ray->o = add_vectors(&(light_ray->o), &(ray->hit));
	if (light->parallel)
	{
		light_ray->dir = multiply_vector(&(light->o), -1.0);
		set_normalized(&(light_ray->dir));
		light_ray->t = 1000000;
	}
	else
	{
		light_ray->dir = sub_vectors(&(light->o), &(light_ray->o));
		light_ray->t = sqrt(set_normalized(&(light_ray->dir)));
	}
}

void	apply_light(t_scene *scene, t_ray *ray, t_light *light)
{
	t_ray		light_ray;
	t_ray		temp_light;
	double		cos;
	double		norme_squarred;

	cos = set_light_ray(ray, light, &light_ray, &norme_squarred);
	if (cos < EPSILON && cos > -EPSILON)
		return ;
	if (cos < EPSILON && (ray->nearest_object->type == SPHERE
			|| ray->nearest_object->type == CONE
			|| ray->nearest_object->type == CYLINDER))
		return ;
	set_temp_light_ray(ray, light, &temp_light);
	if (!is_illuminated(scene, &light_ray, ray, &temp_light))
		return ;
	apply_light_effects(ray, light, cos * (50 / norme_squarred));
}
