/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_box.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 04:15:51 by romain            #+#    #+#             */
/*   Updated: 2022/01/07 17:05:53 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKY_BOX_H
# define SKY_BOX_H

# include "vector.h"

typedef struct s_square_top
{
	static const t_point	o = {0, 0, 10000, 0};
	static const t_vector	normal = {0, 0, -1, 0};
	static const t_point	a = {0, -10000, 10000, 10000};
	static const t_vector	ab = {0, 20001, 0, 0};
	static const t_vector	ad = {0, 0, 0, -20001}
		static const double	radius = 20001;
}					t_top;

typedef struct s_square_bot
{
	static const t_point	o = {0, 0, -10000, 0};
	static const t_vector	normal = {0, 0, 1, 0};
	static const t_point	a = {0, -10000, -10000, 10000};
	static const t_vector	ab = {0, 20001, 0, 0};
	static const t_vector	ad = {0, 0, 0, -20001}
		static const double	radius = 20001;
}				t_bot;

typedef struct s_square_north
{
	static const t_point	o = {0, 0, 0, 10000};
	static const t_vector	normal = {0, 0, 0, -1};
	static const t_point	a = {0, -10000, 10000, 10000};
	static const t_vector	ab = {0, 20001, 0, 0};
	static const t_vector	ad = {0, 0, -20001, 0}
		static const double	radius = 20001;
}				t_north;

typedef struct s_square_south
{
	static const t_point	o = {0, 0, 0, -10000};
	static const t_vector	normal = {0, 0, 0, 1};
	static const t_point	a = {0, 10000, 10000, -10000};
	static const t_vector	ab = {0, -20001, 0, 0};
	static const t_vector	ad = {0, 0, -20001, 0}
		static const double	radius = 20001;
}				t_south;

typedef struct s_square_east
{
	static const t_point	o = {0, -10000, 0, 0};
	static const t_vector	normal = {0, -1, 0, 0};
	static const t_point	a = {0, -10000, 10000, -10000};
	static const t_vector	ab = {0, 0, 0, 20001};
	static const t_vector	ad = {0, 0, -20001, 0}
		static const double	radius = 20001;
}				t_east;

typedef struct s_square_west
{
	static const t_point	o = {0, 10000, 0, 0};
	static const t_vector	normal = {0, 1, 0, 0};
	static const t_point	a = {0, 10000, 10000, 10000};
	static const t_vector	ab = {0, 0, 0, -20001};
	static const t_vector	ad = {0, 0, -20001, 0}
		static const double	radius = 20001;
}				t_west;
