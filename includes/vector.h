/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:08:40 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/27 22:18:10 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067

typedef struct		s_3d_vector
{
	double		x;
	double		y;
	double		z;
}			t_vector;

typedef t_vector	t_point;

t_vector		add_vectors(t_vector *vec1, t_vector *vec2);
t_vector		subtract_vectors(t_vector *vec1, t_vector *vec2);
t_vector		multiply_vector(t_vector *vec1, double doub);
t_vector		divide_vector(t_vector *vec1, double doub);
void			set_vector(t_vector *vec1, double _x,
							double _y, double _z);

t_vector		get_vector_product(t_vector *vec1, t_vector *vec2);
double			get_scalar_product(t_vector *vec1, t_vector *vec2);
double			get_norme(t_vector *vec1);
void			get_normalized(t_vector *vec1);

#endif
