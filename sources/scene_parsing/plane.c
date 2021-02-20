/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:57:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/19 16:39:56 by rsanchez         ###   ########.fr       */
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
	plane->inter_f = is_intersect_plane;
	plane->normal_f = set_plane_normal;
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
	double		norme;

	plane = malloc(sizeof(t_obj));
	if (!plane)
		return (-1);
	init_zero(plane, sizeof(t_obj));
	plane->next = scene->object;
	scene->object = plane;
	if (!parse_plane(plane, format))
		return (FALSE);
	norme = set_normalized(&(plane->normal));
	if (norme < EPSILON)
		return (FALSE);
	return (TRUE + 4);
}
