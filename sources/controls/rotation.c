/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:53:57 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/18 06:26:25 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"

static void	rotate_cam(t_scene *scene, t_cam *cam, int key)
{
	int		coef;
	t_vector	temp;

	coef = scene->control.coef;
	if (key == UP)
		temp = cam->vertical;
	if (key == DOWN)
	{
		temp = cam->vertical;
		coef *= -1;
	}
	if (key == RIGHT)
		temp = cam->horizontal;
	if (key == LEFT)
	{
		temp = cam->horizontal;
		coef *= -1;
	}
	set_normalized(&temp);
	temp = multiply_vector(&temp, 0.1 * coef);
	cam->look_at = add_vectors(&(cam->look_at), &temp);
	set_normalized(&(cam->look_at));
	param_camera(cam, scene->img.line_w, scene->img.col_h);
}

/*
**	printf("direction   %lf   %lf    %lf\n",cam->look_at.x, cam->look_at.y, cam->look_at.z); 
**	printf("vup   %lf   %lf    %lf\n",cam->vup.x, cam->vup.y, cam->vup.z); 
*/

static void	rotate_vup(t_scene *scene, t_cam *cam, int key)
{
	int		coef;

	coef = scene->control.coef;
	if (key == E)
		cam->vup = get_z_rotation(&(cam->vup), 10 * coef, FALSE);
	if (key == A)
		cam->vup = get_z_rotation(&(cam->vup), -10 * coef, FALSE);
	set_normalized(&(cam->vup));
	param_camera(cam, scene->img.line_w, scene->img.col_h);
}

void	rotate_obj(t_scene *scene, t_obj *obj, int key, int coef)
{
	coef = scene->control.coef * 10;
	if (obj->main)
		obj = obj->main;
	if (key == E)
		obj->normal = get_z_rotation(&(obj->normal), coef, FALSE);
	else if (key == A)
		obj->normal = get_z_rotation(&(obj->normal), -1 * coef, FALSE);
	else if (key == UP)
		obj->normal = get_x_rotation(&(obj->normal), coef, FALSE);
	else if (key == DOWN)
		obj->normal = get_x_rotation(&(obj->normal), -1 * coef, FALSE);
	else if (key == LEFT)
		obj->normal = get_y_rotation(&(obj->normal), coef, FALSE);
	else if (key == RIGHT)
		obj->normal = get_y_rotation(&(obj->normal), -1 * coef, FALSE);
	set_normalized(&obj->normal);
	printf("do we enter?\n");
	if (obj->type == SQUARE || obj->type == CUBE || obj->type == PYRAMIDE)
		set_edges(obj);
	if (obj->type == CUBE)
		reset_cube(obj);
	else if (obj->type == PYRAMIDE)
		reset_new_triangle(obj);
	else if (obj->type == CYLINDER && obj->caps)
		reset_disk(obj);
}

void	rotate_lobby(t_scene *scene, int key)
{
	if (scene->control.coef == 0)
		scene->control.coef = 1;
	if (scene->control.selected_obj)
		rotate_obj(scene, scene->control.selected_obj, key, 0);
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		rotate_cam(scene, scene->cam, key);
	else if (key == A || key == E)
		rotate_vup(scene, scene->cam, key);
	ray_caster(scene, scene->mlx, scene->window);
}
