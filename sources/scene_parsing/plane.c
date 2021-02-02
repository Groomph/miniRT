/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:57:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/02 12:55:36 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static int	parse_plane(t_obj *plane, char *format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(plane->o), format, &i)
		|| !vector_microparser(&(plane->normal), format, &i)
		|| !color_microparser(&(plane->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	plane->type = PLANE;
	plane->inter_f = is_intercept_plane;
	plane->normal_f = set_plane_normal;
	plane->specular = FALSE;
	printf("        %.1lf,%.1lf,%.1lf      ", plane->o.x, plane->o.y,
								plane->o.z);
	printf("        %.1lf,%.1lf,%.1lf      ", plane->normal.x, plane->normal.y,
								plane->normal.z);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", plane->color.other,
			plane->color.x, plane->color.y, plane->color.z);
	return (TRUE);
}

int			add_plane(t_scene *scene, char *format)
{
	t_obj		*plane;
	t_vector	edge1;
	t_vector	edge2;
	double		norme;

	plane = malloc(sizeof(t_obj));
	if (!plane)
		return (FALSE);
	plane->next = scene->object;
	scene->object = plane;
	if (!parse_plane(plane, format))
		return (-1);
	if (plane->normal.x == 0.0 && plane->normal.y == 0.0
					&& plane->normal.z == 0.0)
		return (-1);
	set_normalized(&(plane->normal));
	return (TRUE + 4);
}