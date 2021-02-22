/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_disruption.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:12:11 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/22 19:37:48 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void	water(t_vector *p, t_vector *normal)
{
	t_vector	temp;
	double		e;

	e = 5;
	temp.x = noise(p->x - e, p->y, p->z)
		- noise(p->x + e, p->y, p->z);
	temp.y = noise(p->x, p->y - e, p->z)
		- noise(p->x, p->y + e, p->z);
	temp.z = noise(p->x, p->y, p->z - e)
		- noise(p->x, p->y, p->z + e);
	set_normalized(&temp);
	*normal = add_vectors(normal, &temp);
	set_normalized(normal);
}

void	wave(t_vector *p, t_vector *normal)
{
	double		e;

	e = 2;
	if (!(p->y < EPSILON && p->y > -EPSILON))
		normal->y += sin(e * p->y);
	else if (!(p->z < EPSILON && p->z > -EPSILON))
		normal->z += sin(e * p->z);
	else
		normal->x += sin(e * p->x);
	set_normalized(normal);
}
