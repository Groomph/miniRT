/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/02/02 12:53:52 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

BOOL		set_object_bonus(t_obj *obj, char *format, int i)
{
	while (format[i] == ' ')
		i++;
	if (str_n_comp(&(format[i]), "SPECULAR", 8) == 0 && (i += 8))
		obj->specular = TRUE;
	else
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (set_object_bonus(obj, format, i));
	return (TRUE);
}

static int	add_bonus(t_scene *scene, char *format, int previous)
{
	int	check;

	if (previous == 20)
		return (-3);
	else if (previous == 3)
		check = set_camera_bonus(scene->cam_list, format, 5);
	else if (previous == 4)
		check = set_light_bonus(scene->light, format, 5);
	else if (previous >= 5)
		check = set_object_bonus(scene->object, format, 5);
	else
		check = -2;
	if (check == FALSE)
		return (FALSE);
	return (20);
}

int			add_object(t_scene *scene, char *line, int line_nb, int prev)
{
	int check;

	if (str_n_comp(line, "//", 2) == 0)
		return (prev);
	else if (str_n_comp(line, "R ", 2) == 0)
		check = set_resolution(&(scene->img), line);
	else if (str_n_comp(line, "A ", 2) == 0)
		check = set_ambient_light(scene, line);
	else if (str_n_comp(line, "c ", 2) == 0)
		check = add_camera(scene, line);
	else if (str_n_comp(line, "l ", 2) == 0)
		check = add_light(scene, line);
	else if (str_n_comp(line, "sp ", 3) == 0)
		check = add_sphere(scene, line);
	else if (str_n_comp(line, "tr ", 3) == 0)
		check = add_triangle(scene, line);
	else if (str_n_comp(line, "pl ", 3) == 0)
		check = add_plane(scene, line);
	else if (str_n_comp(line, "BONUS ", 6) == 0)
		check = add_bonus(scene, line, prev);
	else
		check = -2;
	if (check < TRUE)
		stop_program(scene, check + 6, line_nb);
	return (check);
}
