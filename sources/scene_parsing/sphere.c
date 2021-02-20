/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:13:44 by romain            #+#    #+#             */
/*   Updated: 2021/02/19 16:26:10 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static int	parse_sphere(t_obj *sphere, char *format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(sphere->o), format, &i)
		|| !double_microparser(&(sphere->radius), format, &i)
		|| sphere->radius <= EPSILON
		|| !color_microparser(&(sphere->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	sphere->type = SPHERE;
	sphere->inter_f = is_intersect_sphere;
	sphere->normal_f = set_sphere_normal;
	printf("        %.1lf,%.1lf,%.1lf      ", sphere->o.x, sphere->o.y,
								sphere->o.z);
	printf("%.2lf    ", sphere->radius);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", sphere->color.other,
			sphere->color.x, sphere->color.y, sphere->color.z);
	return (TRUE);
}

int			add_sphere(t_scene *scene, char *format)
{
	t_obj		*sphere;

	sphere = malloc(sizeof(t_obj));
	if (!sphere)
		return (-1);
	init_zero(sphere, sizeof(t_obj));
	sphere->next = scene->object;
	scene->object = sphere;
	if (!parse_sphere(sphere, format))
		return (FALSE);
	return (TRUE + 4);
}
