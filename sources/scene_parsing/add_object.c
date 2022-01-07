/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2022/01/07 15:04:15 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

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
		return (add_cube(scene, line));
	else if (str_n_comp(line, "py ", 3) == 0)
		return (add_pyramide(scene, line));
	else if (str_n_comp(line, "co ", 3) == 0)
		return (add_cone(scene, line));
	else
		return (-2);
}

int	add_object(t_scene *scene, char *line, int prev)
{
	int	check;

	if (str_n_comp(line, "//", 2) == 0)
		return (prev);
	else if (str_n_comp(line, "BONUS ", 6) == 0)
		check = add_bonus(scene, line, prev);
	else if (str_n_comp(line, "SKYBOX", 6) == 0)
		check = add_sky_box(scene, line);
	else if (str_n_comp(line, "R ", 2) == 0)
		check = set_resolution(scene, &(scene->img), line);
	else if (str_n_comp(line, "A ", 2) == 0)
		check = set_ambient_light(scene, line);
	else if (str_n_comp(line, "c ", 2) == 0)
		check = add_camera(scene, line);
	else if (str_n_comp(line, "l ", 2) == 0)
		check = add_light(scene, line);
	else if (str_n_comp(line, "mt ", 3) == 0)
		check = set_multi_threading(scene, line);
	else
		check = add_object2(scene, line);
	return (check);
}
