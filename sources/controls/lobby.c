/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:10:49 by romain            #+#    #+#             */
/*   Updated: 2021/02/18 07:13:13 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdio.h>

static void	set_coef(t_control *control, int key)
{
	if (key == PLUS)
		control->coef++;
	if (key == MINUS)
		control->coef--;
	if (control->coef < 1)
		control->coef = 1;
	printf("Coef set at %d\n", control->coef * control->coef);
}

int			press_key(int key, t_scene *scene)
{
	printf("%d\n", key);
	if (key == N)
	{
		if (!(scene->cam->next) && scene->cam == scene->cam_list)
			return (1);
		else if (!(scene->cam->next))
			scene->cam = scene->cam_list;
		else
			scene->cam = scene->cam->next;
		ray_caster(scene, scene->mlx, scene->window);
	}
	else if (key == ESCAPE)
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
	return (1);
}

int			press_mouse_button(int key, int x, int y, t_scene *scene)
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
		ray_caster(scene, scene->mlx, scene->window);
	}
	return (1);
}
