/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:10:49 by romain            #+#    #+#             */
/*   Updated: 2021/02/17 20:31:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdio.h>

int	press_key(int key, t_scene *scene)
{
	printf("%d\n", key);
	if (key == N)
	{
		if (!(scene->cam->next))
		{
			if (scene->cam == scene->cam_list)
			{
				printf("There is only one cam\n");
				return (1);
			}
			scene->cam = scene->cam_list;
		}
		else
			scene->cam = scene->cam->next;
	}
	else if (key == ESCAPE)
		stop_program(scene);
	else
		return (1);
	ray_caster(scene, scene->mlx, scene->window);
	return (1);
}

//int	mouse_key(int key, int x, int y, t_scene *scene)

void	loltest(int key, t_scene *scene)
{
	int	x;
	int	y;

	printf("coucou1\n");
	mlx_mouse_get_pos(scene->mlx, scene->window, &x, &y);
	//printf("coucou2\n");

}

int	press_mouse_button(int key, int x, int y, t_scene *scene)
{
	//loltest(key, scene);
	printf("key: %d    x: %d   y: %d\n", key, x, y);
	return (1);
}
