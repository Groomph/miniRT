/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:28:08 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 14:59:16 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>

/*
**		printf("pixel: %d\n", thread->pixel);
**		printf("y: %d\n", thread->y);
**		printf("max_y: %d\n", thread->max_y);
**		printf("i: %d\n", i);
*/

static void	press_key2(int key, t_scene *scene)
{
	if (key == N)
	{
		if (!(scene->cam->next) && scene->cam == scene->cam_list)
		{
			printf("There is only one camera\n");
			return ;
		}
		else if (!(scene->cam->next))
			scene->cam = scene->cam_list;
		else
			scene->cam = scene->cam->next;
		launch_threads(scene);
	}
	else if (key == R || key == T)
		set_threads_number(scene, key);
	else if (key == ENTER)
		launch_threads(scene);
}

int	press_key(int key, t_scene *scene)
{
	if (key == ESCAPE)
		stop_program(scene);
	else if (key == Z || key == S || key == Q || key == D
		|| key == CTRL || key == SPACE)
		translat_lobby(scene, key, scene->control.selected_obj);
	else if (key == A || key == E || key == UP || key == DOWN
		|| key == LEFT || key == RIGHT)
		rotate_lobby(scene, key);
	else if (key == TAB)
		scene->control.selected_obj = NULL;
	else if (key == PLUS || key == MINUS)
		set_coef(&(scene->control), key);
	else
		press_key2(key, scene);
	return (1);
}

int	press_mouse_button(int key, int x, int y, t_scene *scene)
{
	t_ray	ray;

	set_ray(scene, &ray, (double)x, (double)y);
	if (key == 3)
	{
		if (find_nearest_object(scene, &ray))
			scene->control.selected_obj = ray.nearest_object;
		else
			printf("No object there. x: %d y: %d\n", x, y);
	}
	else
	{
		scene->cam->look_at = ray.dir;
		param_camera(scene->cam, scene->img.line_w, scene->img.col_h);
		launch_threads(scene);
	}
	return (1);
}
