/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:08:40 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/01 18:57:33 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define PI 3.1415926535897932384626433832795028841971693993751058209749445923
# define EPSILON 0.00001

typedef struct		s_3d_vector
{
	double		x;
	double		y;
	double		z;
	double		other;
}			t_vector;

typedef struct		s_resolv_triangle
{
	t_vector	edge1;
	t_vector	edge2;
	double		cos;
	t_vector	h;
	t_vector	q;
	double		v;
}			t_tri;

typedef t_vector	t_point;
typedef t_vector	t_color;

t_vector		add_vectors(t_vector *vec1, t_vector *vec2);
t_vector		sub_vectors(t_vector *vec1, t_vector *vec2);
t_vector		multiply_vector(t_vector *vec1, double doub);
t_vector		divide_vector(t_vector *vec1, double doub);
t_vector		get_vector(double oo, double xx, double yy, double zz);

t_vector		get_vector_product(t_vector *vec1, t_vector *vec2);
double			get_scalar_product(t_vector *vec1, t_vector *vec2);
double			get_norme(t_vector *vec1);
double			set_normalized(t_vector *vec1);
t_point			get_x_rotation(t_vector *vec, double theta);
t_point			get_y_rotation(t_vector *vec, double theta);
t_point			get_z_rotation(t_vector *vec, double theta);
#endif
