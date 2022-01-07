/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:53:57 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 14:58:41 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"

static void	translat_cam(t_scene *scene, int key)
{
	int			coef;
	t_vector	temp;

	coef = scene->control.coef;
	coef *= coef;
	if (key == SPACE)
		temp = scene->cam->vertical;
	if (key == CTRL)
		temp = multiply_vector(&(scene->cam->vertical), -1.0);
	if (key == Z)
		temp = scene->cam->look_at;
	if (key == S)
		temp = multiply_vector(&(scene->cam->look_at), -1.0);
	if (key == Q)
		temp = scene->cam->horizontal;
	if (key == D)
		temp = multiply_vector(&(scene->cam->horizontal), -1.0);
	set_normalized(&temp);
	temp = multiply_vector(&temp, 0.1 * coef);
	scene->cam->o = add_vectors(&(scene->cam->o), &temp);
	scene->cam->lower_corner = add_vectors(&(scene->cam->lower_corner), &temp);
}

static void	translat_object(t_scene *scene, t_point *o, int key)
{
	int		coef;

	coef = scene->control.coef;
	coef *= coef;
	if (key == SPACE)
		o->y += 0.10 * coef;
	if (key == CTRL)
		o->y -= 0.10 * coef;
	if (key == Z)
		o->z += 0.10 * coef;
	if (key == S)
		o->z -= 0.10 * coef;
	if (key == Q)
		o->x += 0.10 * coef;
	if (key == D)
		o->x -= 0.10 * coef;
}

static void	special_obj(t_scene *scene, t_obj *obj, int key, t_obj *main)
{
	translat_object(scene, &(obj->o), key);
	if (obj->type == CUBE || (obj->type == PYRAMIDE && obj == main))
		translat_object(scene, &(obj->a), key);
	else if (obj->type == PYRAMIDE && obj != main)
	{
		translat_object(scene, &(obj->o2), key);
		translat_object(scene, &(obj->o3), key);
	}
	if (obj->next->main == main)
		special_obj(scene, obj->next, key, obj->main);
}

/*
**static void	translat_special_object(t_scene *scene, t_obj *obj, key, int i)
**{
**	int		i;
**
**	if (obj->type == DISK || obj->type == CUBE || obj->type == PYRAMIDE)
**		obj = obj->main;
**	i = -1;
**	if (obj->type == CYLINDER)
**	{
**		while (++i < 3)
**		{
**			translat_object(scene, &(obj->o), key);
**			obj = obj->next;
**		}
**	}
**	else if (obj->type == CUBE)
**	{
**		while (++i < 6)
**		{
**			translat_object(scene, &(obj->o), key);
**			translat_object(scene, &(obj->a), key);
**			obj = obj->next;
**		}
**	}
**	else if (obj->type == PYRAMIDE)
**	{
**		translat_object(scene, &(obj->o), key);
**		translat_object(scene, &(obj->a), key);
**		obj = obj->next;
**		while (++i < 4)
**		{
**			translat_object(scene, &(obj->o), key);
**			translat_object(scene, &(obj->o2), key);
**			translat_object(scene, &(obj->o3), key);
**		}
**	}
**}
*/

void	translat_lobby(t_scene *scene, int key, t_obj *obj)
{
	if (scene->control.coef == 0)
		scene->control.coef = 1;
	if (obj == NULL)
		translat_cam(scene, key);
	else if (obj->type == SPHERE || obj->type == PLANE
		|| obj->type == CONE)
		translat_object(scene, &(obj->o), key);
	else if (obj->type == TRIANGLE)
	{
		translat_object(scene, &(obj->o), key);
		translat_object(scene, &(obj->o2), key);
		translat_object(scene, &(obj->o3), key);
	}
	else if (obj->type == SQUARE)
	{
		translat_object(scene, &(obj->o), key);
		translat_object(scene, &(obj->a), key);
	}
	else if (obj->type == CYLINDER && !obj->caps)
		translat_object(scene, &(obj->o), key);
	else
		special_obj(scene, obj->main, key, obj->main);
	launch_threads(scene);
}
