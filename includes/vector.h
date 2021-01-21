/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:08:40 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/20 21:55:24 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067
# define get_norme(x) get_scalar_product(x, x)

typedef struct		s_3d_vector
{
	double		x;
	double		y;
	double		z;
	double		other;
}			t_vector;

typedef t_vector	t_point;
typedef t_vector	t_color;

t_vector		add_vectors(t_vector *vec1, t_vector *vec2);
t_vector		sub_vectors(t_vector *vec1, t_vector *vec2);
t_vector		multiply_vector(t_vector *vec1, double doub);
t_vector		divide_vector(t_vector *vec1, double doub);
t_vector		get_vector(double oo, double xx, double yy, double zz);

t_vector		get_vector_product(t_vector *vec1, t_vector *vec2);
double			get_scalar_product(t_vector *vec1, t_vector *vec2);
//double			get_norme(t_vector *vec1);
void			set_normalized(t_vector *vec1);
int			fuse_vector(t_vector *vec);
#endif
