/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:08:40 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/09 15:12:05 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define PI 3.1415926535897932384626433832795028841971693993751058209749445923
# define PI_2 1.57079632679489661923
# define EPSILON 0.000001
# define BOOL int
# define TRUE 1
# define FALSE 0

typedef struct		s_3d_vector
{
	double		x;
	double		y;
	double		z;
	double		other;
}			t_vector;

typedef t_vector	t_point;
typedef t_vector	t_color;

typedef struct		s_resolv_triangle
{
	t_vector	edge1;
	t_vector	edge2;
	double		cos;
	t_vector	h;
	t_vector	q;
}			t_tri;

typedef struct		s_resolv_square
{
	t_point		a;
	t_point		b;
	t_point		c;
	t_point		d;
	double		cos;
	t_vector	h;
	t_vector	q;
}			t_squ;

typedef struct		s_resolv_cylinder
{
	double		a;
	double		b;
	double		c;
	double		delta;
	t_vector	u;
	t_vector	v;
}			t_cyl;

t_vector		add_vectors(t_vector *vec1, t_vector *vec2);
t_vector		sub_vectors(t_vector *vec1, t_vector *vec2);
t_vector		multiply_vector(t_vector *vec1, double doub);
t_vector		divide_vector(t_vector *vec1, double doub);
t_vector		get_vector(double oo, double xx, double yy, double zz);

t_vector		get_vector_product(t_vector *vec1, t_vector *vec2);
double			get_scalar_product(t_vector *vec1, t_vector *vec2);
double			get_norme(t_vector *vec1);
double			set_normalized(t_vector *vec1);
t_vector		get_x_rotation(t_vector *vec, double theta, BOOL is_radian);
t_vector		get_y_rotation(t_vector *vec, double theta, BOOL is_radian);
t_vector		get_z_rotation(t_vector *vec, double theta, BOOL is_radian);
void			set_full_rotation(t_vector *vec, t_vector *normed_dir);
#endif
