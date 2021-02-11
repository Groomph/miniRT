/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:10:49 by romain            #+#    #+#             */
/*   Updated: 2021/02/11 00:38:50 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
