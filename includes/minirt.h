/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:34:51 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/21 18:44:14 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "vector.h"

# define BOOL int
# define TRUE 1
# define FALSE 0

# define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067

typedef struct		s_sphere
{
	t_vector	origin;
	double		radius;
}			t_sphere;

BOOL			is_intercept_sphere(t_vector *ray_o, t_vector *ray_dir, t_sphere *sphere);

#endif
