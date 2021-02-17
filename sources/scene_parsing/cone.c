/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 22:13:57 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/17 16:49:10 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static int	parse_cone(t_obj *cone, char *format, int i)
{
	if (!vector_microparser(&(cone->o), format, &i)
		|| !vector_microparser(&(cone->normal), format, &i)
		|| !double_microparser(&(cone->radius), format, &i)
		|| !double_microparser(&(cone->h), format, &i)
		|| cone->radius <= EPSILON || cone->radius >= 180 
		|| cone->h <= EPSILON
		|| !color_microparser(&(cone->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	cone->radius = cone->radius / 2 * (PI / 180);
	cone->type = CONE;
	cone->inter_f = is_intersect_cone;
	cone->normal_f = set_cone_normal;
	cone->specular = FALSE;
	printf("  %.1lf,%.1lf,%.1lf  ", cone->o.x, cone->o.y,
								cone->o.z);
	printf("     %.1lf,%.1lf,%.1lf", cone->normal.x,
					cone->normal.y, cone->normal.z);
	printf("%.2lf    ", cone->radius);
	printf("%.2lf    ", cone->h);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", cone->color.other,
			cone->color.x, cone->color.y, cone->color.z);
	return (TRUE);
}

int			add_cone(t_scene *scene, char *format)
{
	t_obj		*cone;
	double		norme;

	cone = malloc(sizeof(t_obj));
	if (!cone)
		return (-1);
	cone->next = scene->object;
	scene->object = cone;
	if (!parse_cone(cone, format, 2))
		return (FALSE);
	norme = set_normalized(&(cone->normal));
	if (norme == 0)
		return (FALSE);
	cone->check_board = FALSE;
	cone->rainbow = FALSE;
	return (TRUE + 4);
}
