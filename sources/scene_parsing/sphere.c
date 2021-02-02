/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:13:44 by romain            #+#    #+#             */
/*   Updated: 2021/02/01 23:37:47 by rsanchez         ###   ########.fr       */
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
		|| sphere->radius <= 0
		|| !color_microparser(&(sphere->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	sphere->type = SPHERE;
	sphere->inter_f = is_intercept_sphere;
	sphere->normal_f = set_sphere_normal;
	sphere->specular = FALSE;
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
		return (FALSE);
	sphere->next = scene->object;
	scene->object = sphere;
	if (!parse_sphere(sphere, format))
		return (-1);
	return (TRUE + 4);
}