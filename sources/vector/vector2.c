/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:11:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/18 17:22:18 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

long double	scalar_product(t_vector *vec1, t_vector *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

long double	norme_squarred(t_vector *vec1)
{
	return (vec1->x * vec1->x + vec1->y * vec1->y + vec1->z * vec1->z);
}

void		normalized(t_vector *vec1)
{
	long double	norme;

	norme = norme_squarred(vec1);
	vec1->x /= norme;
	vec1->y /= norme;
	vec1->z /= norme;
}
