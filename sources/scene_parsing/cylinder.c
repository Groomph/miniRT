/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:13:44 by romain            #+#    #+#             */
/*   Updated: 2022/01/07 15:51:55 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

void	reset_disk(t_obj *first)
{
	t_obj	*disk;

	disk = first->next;
	disk->normal = first->normal;
	disk->o = first->o;
	disk = disk->next;
	disk->normal = first->normal;
	disk->o = multiply_vector(&(first->normal), first->h);
	disk->o = add_vectors(&(disk->o), &(first->o));
}

int	add_disk(t_scene *scene, t_obj *cylinder, int i)
{
	t_obj		*disk;

	disk = malloc(sizeof(t_obj));
	if (!disk)
		return (FALSE);
	init_zero(disk, sizeof(t_obj));
	disk->o = cylinder->o;
	disk->normal = cylinder->normal;
	disk->radius = cylinder->radius;
	disk->color = cylinder->color;
	disk->inter_f = is_intersect_disk;
	disk->normal_f = set_disk_normal;
	disk->type = DISK;
	disk->main = cylinder;
	disk->next = cylinder->next;
	cylinder->next = disk;
	if (i == 0)
	{
		cylinder->o = multiply_vector(&(cylinder->normal), cylinder->h);
		cylinder->o = add_vectors(&(disk->o), &(cylinder->o));
		if (!add_disk(scene, cylinder, 1))
			return (FALSE);
		cylinder->o = disk->o;
	}
	return (TRUE);
}

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

int	add_cylinder(t_scene *scene, char *format)
{
	t_obj		*cylinder;
	double		norme;

	cylinder = malloc(sizeof(t_obj));
	if (!cylinder)
		return (-1);
	init_zero(cylinder, sizeof(t_obj));
	cylinder->next = scene->object;
	scene->object = cylinder;
	if (!parse_cylinder(cylinder, format, 2))
		return (FALSE);
	norme = set_normalized(&(cylinder->normal));
	if (norme == 0)
		return (FALSE);
	return (TRUE + 4);
}
