/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:11:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/18 17:21:05 by romain           ###   ########.fr       */
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

t_vector	multiply_vectors(long double doub, t_vector *vec1)
{
	t_vector	tmp;

	tmp.x = vec1->x * doub;
	tmp.y = vec1->y * doub;
	tmp.z = vec1->z * doub;
	return (tmp);
}

t_vector	divide_vectors(long double doub, t_vector *vec1)
{
	t_vector	tmp;

	tmp.x = vec1->x / doub;
	tmp.y = vec1->y / doub;
	tmp.z = vec1->z / doub;
	return (tmp);
}
