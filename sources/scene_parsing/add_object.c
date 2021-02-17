/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/02/12 22:34:47 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

BOOL		set_object_bonus(t_scene *scene, t_obj *obj, char *format, int i)
{
	while (format[i] == ' ')
		i++;
	if (str_n_comp(&(format[i]), "SPECULAR", 8) == 0 && (i += 8))
		obj->specular = TRUE;
	else if (str_n_comp(&(format[i]), "CAPS", 4) == 0 && (i += 4))
		obj->caps = TRUE;
	else
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (set_object_bonus(scene, obj, format, i));
	if (obj->caps == TRUE)
	       	if (obj->type != CYLINDER || !add_disk(scene, obj, 0))
			return (FALSE);
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
		check = set_object_bonus(scene, scene->object, format, 5);
	else
		check = -2;
	if (check < TRUE)
		return (FALSE);
	return (20);
}

static int	add_object2(t_scene *scene, char *line)
{
	if (str_n_comp(line, "sp ", 3) == 0)
		return (add_sphere(scene, line));
	else if (str_n_comp(line, "tr ", 3) == 0)
		return (add_triangle(scene, line));
	else if (str_n_comp(line, "pl ", 3) == 0)
		return (add_plane(scene, line));
	else if (str_n_comp(line, "sq ", 3) == 0)
		return (add_square(scene, line));
	else if (str_n_comp(line, "cy ", 3) == 0)
		return (add_cylinder(scene, line));
	else if (str_n_comp(line, "cu ", 3) == 0)
		return (add_cube(scene, line, 0));
	else
		return (-2);
}

int			add_object(t_scene *scene, char *line, int prev)
{
	int check;

	if (str_n_comp(line, "//", 2) == 0)
		return (prev);
	else if (str_n_comp(line, "BONUS ", 6) == 0)
		check = add_bonus(scene, line, prev);
	else if (str_n_comp(line, "R ", 2) == 0)
		check = set_resolution(scene, &(scene->img), line);
	else if (str_n_comp(line, "A ", 2) == 0)
		check = set_ambient_light(scene, line);
	else if (str_n_comp(line, "c ", 2) == 0)
		check = add_camera(scene, line);
	else if (str_n_comp(line, "l ", 2) == 0)
		check = add_light(scene, line);
	else
		check = add_object2(scene, line);
	return (check);
}
