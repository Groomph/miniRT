/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:11:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 22:09:46 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	add_vectors(t_vector *vec1, t_vector *vec2)
{
	t_vector	tmp;

	tmp.x = vec1->x + vec2->x;
	tmp.y = vec1->y + vec2->y;
	tmp.z = vec1->z + vec2->z;
	return (tmp);
}

t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2)
{
	t_vector	tmp;

	tmp.x = vec1->x - vec2->x;
	tmp.y = vec1->y - vec2->y;
	tmp.z = vec1->z - vec2->z;
	return (tmp);
}

t_vector	multiply_vector(t_vector *vec1, double doub)
{
	t_vector	tmp;

	tmp.x = vec1->x * doub;
	tmp.y = vec1->y * doub;
	tmp.z = vec1->z * doub;
	return (tmp);
}

t_vector	divide_vector(t_vector *vec1, double doub)
{
	t_vector	tmp;

	tmp.x = vec1->x / doub;
	tmp.y = vec1->y / doub;
	tmp.z = vec1->z / doub;
	return (tmp);
}

void		set_vector(t_vector *vec1, double _x, double _y, double _z)
{
	vec1->x = _x;
	vec1->y = _y;
	vec1->z = _z;
}
