/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:08:40 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/21 18:39:54 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}		t_vector;

t_vector	add_vectors(t_vector *vec1, t_vector *vec2);
t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2);
t_vector	multiply_vectors(double doub, t_vector *vec2);
t_vector	divide_vectors(double doub, t_vector *vec2);

t_vector	get_vector_product(t_vector *vec1, t_vector *vec2);
double		get_scalar_product(t_vector *vec1, t_vector *vec2);
double		get_norme(t_vector *vec1);
void		get_normalized(t_vector *vec1);

#endif
