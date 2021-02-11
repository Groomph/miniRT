/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:13:44 by romain            #+#    #+#             */
/*   Updated: 2021/02/09 15:56:38 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static int	parse_cylinder(t_obj *cylinder, char *format, int i)
{
	if (!vector_microparser(&(cylinder->o), format, &i)
		|| !vector_microparser(&(cylinder->normal), format, &i)
		|| !double_microparser(&(cylinder->radius), format, &i)
		|| !double_microparser(&(cylinder->h), format, &i)
		|| cylinder->radius <= EPSILON || cylinder->h <= EPSILON
		|| !color_microparser(&(cylinder->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	cylinder->radius /= 2.0;
	cylinder->type = CYLINDER;
	cylinder->inter_f = is_intersect_cylinder;
	cylinder->normal_f = set_cylinder_normal;
	cylinder->specular = FALSE;
	printf("  %.1lf,%.1lf,%.1lf  ", cylinder->o.x, cylinder->o.y,
								cylinder->o.z);
	printf("     %.1lf,%.1lf,%.1lf", cylinder->normal.x,
					cylinder->normal.y, cylinder->normal.z);
	printf("%.2lf    ", cylinder->radius);
	printf("%.2lf    ", cylinder->h);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", cylinder->color.other,
			cylinder->color.x, cylinder->color.y, cylinder->color.z);
	return (TRUE);
}

int			add_cylinder(t_scene *scene, char *format)
{
	t_obj		*cylinder;
	double		norme;

	cylinder = malloc(sizeof(t_obj));
	if (!cylinder)
		return (-1);
	cylinder->next = scene->object;
	scene->object = cylinder;
	if (!parse_cylinder(cylinder, format, 2))
		return (FALSE);
	norme = set_normalized(&(cylinder->normal));
	if (norme == 0)
		return (FALSE);
	return (TRUE + 4);
}
