/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_getters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:11:58 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/01 20:24:58 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>
#include <stdio.h>

t_vector	get_vector_product(t_vector *vec1, t_vector *vec2)
{
	t_vector	temp;

	temp.x = vec1->y * vec2->z - vec1->z * vec2->y;
	temp.y = vec1->z * vec2->x - vec1->x * vec2->z;
	temp.z = vec1->x * vec2->y - vec1->y * vec2->x;
	return (temp);
}

double		get_scalar_product(t_vector *vec, t_vector *vec2)
{
	return (vec->x * vec2->x + vec->y * vec2->y + vec->z * vec2->z);
}

double		get_norme(t_vector *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

double		set_normalized(t_vector *vec1)
{
	double	norme_squarred;
	double	norme;

	norme_squarred = get_norme(vec1);
	if (norme_squarred > 0.0)
	{
		norme = sqrt(norme_squarred);
		norme = 1 / norme;
		vec1->x *= norme;
		vec1->y *= norme;
		vec1->z *= norme;
	}
	else
	{
		printf("NOT SUPPOSED TO HAPPEN, NORME == 0\n");
	}
	return (norme_squarred);
}
