/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:57:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/18 06:36:33 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static void	set_new_triangle2(t_obj *pyramide, t_obj *first, int i)
{
	if (i == 1)
	{
		pyramide->o = first->b;
		pyramide->o2 = first->c;
	}
	else if (i == 2)
	{
		pyramide->o = first->c;
		pyramide->o2 = first->d;
	}
	else
	{
		pyramide->o = first->d;
		pyramide->o2 = first->a;
	}
}

static void	set_new_triangle(t_obj *pyramide, t_obj *first, int i)
{
	t_vector	edge1;
	t_vector	edge2;

	if (i == 0)
	{
		pyramide->o = first->a;
		pyramide->o2 = first->b;
	}
	else
		set_new_triangle2(pyramide, first, i);
	pyramide->o3 = first->o3;
	pyramide->color = first->color;
	pyramide->type = PYRAMIDE;
	pyramide->main = first;
	pyramide->inter_f = is_intersect_triangle;
	pyramide->normal_f = set_triangle_normal;
	pyramide->specular = FALSE;
	edge1 = sub_vectors(&(pyramide->o2), &(pyramide->o3));
	edge2 = sub_vectors(&(pyramide->o), &(pyramide->o3));
	pyramide->normal = get_vector_product(&edge1, &edge2);
	set_normalized(&(pyramide->normal));
}

static int	parse_pyramide(t_obj *pyramide, char *format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(pyramide->o), format, &i)
		|| !vector_microparser(&(pyramide->normal), format, &i)
		|| !double_microparser(&(pyramide->radius), format, &i)
		|| !double_microparser(&(pyramide->h), format, &i)
		|| pyramide->radius < 0.0 || pyramide->h < 0.0
		|| !color_microparser(&(pyramide->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	pyramide->type = PYRAMIDE;
	pyramide->main = pyramide;
	pyramide->inter_f = is_intersect_square;
	pyramide->normal_f = set_square_normal;
	pyramide->specular = FALSE;
	printf("     %.1lf,%.1lf,%.1lf   ", pyramide->o.x, pyramide->o.y,
							pyramide->o.z);
	printf("     %.1lf,%.1lf,%.1lf   ", pyramide->normal.x,
				pyramide->normal.y, pyramide->normal.z);
	printf("     %.1lf,%.1lf,%.1lf,%.1lf\n\n", pyramide->color.other,
		pyramide->color.x, pyramide->color.y, pyramide->color.z);
	return (TRUE);
}

void		reset_new_triangle(t_obj *first)
{
	int		i;
	t_obj		*triangle;

	i = -1;
	first->o3 = multiply_vector(&(first->normal), first->h);
	first->o3 = add_vectors(&(first->o), &(first->o3));
	triangle = first->next;
	while (++i < 4)
	{
		set_new_triangle(triangle, first, i);
		triangle = triangle->next;
	}
}

int			add_pyramide(t_scene *scene, char *format)
{
	t_obj		*pyramide;
	int			i;

	pyramide = malloc(sizeof(t_obj));
	if (!pyramide)
		return (-1);
	pyramide->next = scene->object;
	scene->object = pyramide;
	if (!parse_pyramide(pyramide, format)
			|| set_normalized(&(pyramide->normal)) == 0)
		return (FALSE);
	set_edges(pyramide);
	pyramide->o3 = multiply_vector(&(pyramide->normal), pyramide->h);
	pyramide->o3 = add_vectors(&(pyramide->o), &(pyramide->o3));
	i = -1;
	while (++i < 4)
	{
		pyramide = malloc(sizeof(t_obj));
		if (!pyramide)
			return (-1);
		pyramide->next = scene->object->next;
		scene->object->next = pyramide;
		set_new_triangle(pyramide, scene->object, i);
	}
	return (TRUE + 4);
}
