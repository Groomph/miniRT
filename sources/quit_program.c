/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/02/02 13:37:04 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

static void	error_printer(int errornb, int line)
{
	char	*error_tab[15];

	error_tab[3] = "Error n°3: Double bonus parameters, line ";
	error_tab[4] = "Error n°4: Wrong object identifier, line ";
	error_tab[5] = "Error n°5: Malloc error, line ";
	error_tab[6] = "Error n°6: Wrong line format, line ";
	error_tab[7] = "Error n°7: Missing essential object(s)";
	error_tab[11] = "Error n°11: Invalid path or file name\n";
	error_tab[12] = "Error n°12: Unknown second argument\n";
	error_tab[13] = "Error n°13: Wrong number of arguments\n";
	error_tab[14] = "Error n°14: Error while reading file\n";
	if (line >= 0)
		printf("%s%d\n", error_tab[errornb], line);
	else
		printf("%s", error_tab[errornb]);
}

void		clear_cams(t_cam **list)
{
	if (list && *list)
	{
		clear_cams(&((*list)->next));
		free(*list);
		*list = NULL;
	}
}

void		clear_lights(t_light **list)
{
	if (list && *list)
	{
		clear_lights(&((*list)->next));
		free(*list);
		*list = NULL;
	}
}

void		clear_objects(t_obj **list)
{
	if (list && *list)
	{
		clear_objects(&((*list)->next));
		free(*list);
		*list = NULL;
	}
}

void		stop_program(t_scene *scene, int errornb, int line)
{
	error_printer(errornb, line);
	clear_cams(&(scene->cam_list));
	clear_lights(&(scene->light));
	clear_objects(&(scene->object));
	exit(0);
}
