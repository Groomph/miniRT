/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:57:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/17 16:49:36 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static void	set_new_square2(t_obj *square, t_obj *first, int i,
							t_vector *translat)
{
	if (i == 1)
	{
		square->a = add_vectors(&(first->d), translat);
		square->b = add_vectors(&(first->a), translat);
		square->d = first->d;
	}
	else if (i == 2)
	{
		square->a = add_vectors(&(first->b), translat);
		square->b = add_vectors(&(first->c), translat);
		square->d = first->b;
	}
	else if (i == 3)
	{
		square->a = add_vectors(&(first->a), translat);
		square->b = add_vectors(&(first->b), translat);
		square->d = first->a;
	}
	else
	{
		square->a = add_vectors(&(first->d), translat);
		square->b = add_vectors(&(first->c), translat);
		square->d = first->d;
	}
}

static void	set_new_square(t_obj *square, t_obj *first, int i)
{
	t_vector	translat;

	translat = multiply_vector(&(first->normal), first->radius);
	if (i == 0)
	{
		square->a = add_vectors(&(first->a), &translat);
		square->b = add_vectors(&(first->b), &translat);
		square->d = add_vectors(&(first->d), &translat);
	}
	else
		set_new_square2(square, first, i, &translat);
	square->ab = sub_vectors(&(square->b), &(square->a));
	square->ad = sub_vectors(&(square->d), &(square->a));
	translat = multiply_vector(&(square->ad), 0.5);
	square->o = add_vectors(&(square->a), &translat);
	translat = multiply_vector(&(square->ab), 0.5);
	square->o = add_vectors(&(square->o), &translat);
	square->color = first->color;
	square->type = SQUARE;
	square->inter_f = is_intersect_square;
	square->normal_f = set_square_normal;
	square->radius = first->radius;
	square->next = first->next;
	first->next = square;
}

int			add_cube(t_scene *scene, char *format)
{
	t_obj		*square;
	double		norme;
	int			i;

	i = add_square(scene, format);
	if (i <= 0)
		return (i);
	scene->object->type = CUBE;
	i = -1;
	while (++i < 5)
	{
		square = malloc(sizeof(t_obj));
		if (!square)
			return (-1);
		set_new_square(square, scene->object, i);
		if (i == 0)
			square->normal = scene->object->normal;
		else if (i >= 3)
			square->normal = scene->object->ad;
		else
			square->normal = scene->object->ab;
		set_normalized(&(square->normal));
	}
	return (TRUE + 4);
}
