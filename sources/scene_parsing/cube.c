/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:57:54 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/12 22:39:07 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <stdio.h>

static int	parse_cube(t_obj *cube, char *format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(cube->o), format, &i)
		|| !vector_microparser(&(cube->normal), format, &i)
		|| !double_microparser(&(cube->radius), format, &i)
		|| cube->radius < 0.0
		|| !color_microparser(&(cube->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	cube->type = CUBE;
	cube->inter_f = is_intersect_cube;
	cube->normal_f = set_cube_normal;
	cube->specular = FALSE;
	printf("        %.1lf,%.1lf,%.1lf      ", cube->o.x, cube->o.y,
			cube->o.z);
	printf("        %.1lf,%.1lf,%.1lf      ", cube->normal.x,
			cube->normal.y, cube->normal.z);
	printf("     %.1lf   ", cube->radius);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", cube->color.other,
			cube->color.x, cube->color.y, cube->color.z);
	return (TRUE);
}

static void	set_edges2(t_obj *cube, t_vector *x_axe, t_vector *y_axe)
{
	t_vector	half_x_axe;
	t_vector	half_y_axe;
	t_vector	b;
	t_vector	d;

	half_y_axe = divide_vector(y_axe, 2.0);
	half_x_axe = divide_vector(x_axe, 2.0);
	cube->a = add_vectors(&(cube->o), &half_y_axe);
	cube->a = sub_vectors(&cube->a, &half_x_axe);
	b = add_vectors(&(cube->a), x_axe);
	d = sub_vectors(&(cube->a), y_axe);
	cube->ab = sub_vectors(&b, &(cube->a));
	cube->ad = sub_vectors(&d, &(cube->a));
	printf("         %.1lf,%.1lf,%.1lf\n", cube->a.x,
						cube->a.y, cube->a.z);
	printf("         %.1lf,%.1lf,%.1lf\n", b.x, b.y, b.z);
	printf("         %.1lf,%.1lf,%.1lf\n", d.x, d.y, d.z);
}

static void	set_edges(t_obj *cube)
{
	t_vector	x_axe;
	t_vector	y_axe;

	if (cube->normal.z == 1.0 || cube->normal.z == -1.0)
	{
		y_axe = get_vector(0, 0, 1, 0);
		x_axe = get_vector_product(&y_axe, &(cube->normal));
	}
	else
	{
		y_axe = get_z_rotation(&(cube->normal), 90, FALSE);
		x_axe = get_vector_product(&y_axe, &(cube->normal));
	}
	set_normalized(&y_axe);
	set_normalized(&x_axe);
	y_axe = multiply_vector(&y_axe, cube->radius);
	x_axe = multiply_vector(&x_axe, cube->radius);
	set_edges2(cube, &x_axe, &y_axe);
}

/*
**	set_normalized(&y_axe);
**	set_normalized(&x_axe);
*/

int			add_cube(t_scene *scene, char *format)
{
	t_obj		*cube;
	double		norme;

	if (!add_square()
		return (-1);
	cube->next = scene->object;
	scene->object = cube;
	if (!parse_cube(cube, format))
		return (FALSE);
	norme = set_normalized(&(cube->normal));
	if (norme == 0)
		return (FALSE);
	set_edges(cube);
	return (TRUE + 4);
}
