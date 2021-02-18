/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:57:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/18 05:30:36 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static int	parse_triangle(t_obj *triangle, char *format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(triangle->o), format, &i)
		|| !vector_microparser(&(triangle->o2), format, &i)
		|| !vector_microparser(&(triangle->o3), format, &i)
		|| !color_microparser(&(triangle->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	triangle->type = TRIANGLE;
	triangle->inter_f = is_intersect_triangle;
	triangle->normal_f = set_triangle_normal;
	triangle->specular = FALSE;
	printf("        %.1lf,%.1lf,%.1lf      ", triangle->o.x, triangle->o.y,
								triangle->o.z);
	printf("        %.1lf,%.1lf,%.1lf      ", triangle->o2.x, triangle->o2.y,
								triangle->o2.z);
	printf("        %.1lf,%.1lf,%.1lf      ", triangle->o3.x, triangle->o3.y,
								triangle->o3.z);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", triangle->color.other,
			triangle->color.x, triangle->color.y, triangle->color.z);
	return (TRUE);
}

int			add_triangle(t_scene *scene, char *format)
{
	t_obj		*triangle;
	t_vector	edge1;
	t_vector	edge2;
	double		norme;

	triangle = malloc(sizeof(t_obj));
	if (!triangle)
		return (-1);
	triangle->main = NULL;
	triangle->next = scene->object;
	scene->object = triangle;
	if (!parse_triangle(triangle, format))
		return (FALSE);
	edge1 = sub_vectors(&(triangle->o2), &(triangle->o));
	edge2 = sub_vectors(&(triangle->o3), &(triangle->o));
	triangle->normal = get_vector_product(&edge1, &edge2);
	norme = set_normalized(&(triangle->normal));
	if (norme < EPSILON)
		return (FALSE);
	triangle->check_board = FALSE;
	triangle->rainbow = FALSE;
	return (TRUE + 4);
}
