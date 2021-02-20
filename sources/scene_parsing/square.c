/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:57:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/19 16:24:08 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static int	parse_square(t_obj *square, char *format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(square->o), format, &i)
		|| !vector_microparser(&(square->normal), format, &i)
		|| !double_microparser(&(square->radius), format, &i)
		|| square->radius < 0.0
		|| !color_microparser(&(square->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	square->type = SQUARE;
	square->inter_f = is_intersect_square;
	square->normal_f = set_square_normal;
	printf("        %.1lf,%.1lf,%.1lf      ", square->o.x, square->o.y,
			square->o.z);
	printf("        %.1lf,%.1lf,%.1lf      ", square->normal.x,
			square->normal.y, square->normal.z);
	printf("     %.1lf   ", square->radius);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", square->color.other,
			square->color.x, square->color.y, square->color.z);
	return (TRUE);
}

static void	set_edges2(t_obj *square, t_vector *x_axe, t_vector *y_axe)
{
	t_vector	half_x_axe;
	t_vector	half_y_axe;

	half_y_axe = divide_vector(y_axe, 2.0);
	half_x_axe = divide_vector(x_axe, 2.0);
	square->a = sub_vectors(&(square->o), &half_y_axe);
	square->a = sub_vectors(&square->a, &half_x_axe);
	square->b = add_vectors(&(square->a), x_axe);
	square->c = add_vectors(&(square->b), y_axe);
	square->d = add_vectors(&(square->a), y_axe);
	square->ab = sub_vectors(&(square->b), &(square->a));
	square->ad = sub_vectors(&(square->d), &(square->a));
}

void	set_edges(t_obj *square)
{
	t_vector	x_axe;
	t_vector	y_axe;

	if (square->normal.y == 1 || square->normal.y == -1)
		y_axe = get_vector(0, 0, 0, 1);
	else
		y_axe = get_vector(0, 0, 1, 0);
	x_axe = get_vector_product(&y_axe, &(square->normal));
	y_axe = get_vector_product(&x_axe, &(square->normal));
	set_normalized(&y_axe);
	set_normalized(&x_axe);
	y_axe = multiply_vector(&y_axe, square->radius);
	x_axe = multiply_vector(&x_axe, square->radius);
	set_edges2(square, &x_axe, &y_axe);
}

int			add_square(t_scene *scene, char *format)
{
	t_obj		*square;
	double		norme;

	square = malloc(sizeof(t_obj));
	if (!square)
		return (-1);
	init_zero(square, sizeof(t_obj));
	square->next = scene->object;
	scene->object = square;
	if (!parse_square(square, format))
		return (FALSE);
	norme = set_normalized(&(square->normal));
	if (norme == 0)
		return (FALSE);
	set_edges(square);
	return (TRUE + 4);
}
