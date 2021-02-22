/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_box.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 04:15:51 by romain            #+#    #+#             */
/*   Updated: 2021/02/22 04:50:30 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKY_BOX_H
# define SKY_BOX_H

#include "vector.h"

typedef struct		s_square_top
{
	t_point		o = {0, 0, 10000, 0};
	t_vector	normal = {0, 0, -1, 0};
	t_point		a = {0, -10000, 10000, 10000};
	t_vector	ab = {0, 20001, 0, 0};
	t_vector	ad = {0, 0, 0, -20001}
	double		radius = 20001;
}			t_top;

typedef struct		s_square_bot
{
	t_point		o = {0, 0, -10000, 0};
	t_vector	normal = {0, 0, 1, 0};
	t_point		a = {0, -10000, -10000, 10000};
	t_vector	ab = {0, 20001, 0, 0};
	t_vector	ad = {0, 0, 0, -20001}
	double		radius = 20001;
}			t_bot;

typedef struct		s_square_north
{
	t_point		o = {0, 0, 0, 10000};
	t_vector	normal = {0, 0, 0, -1};
	t_point		a = {0, -10000, 10000, 10000};
	t_vector	ab = {0, 20001, 0, 0};
	t_vector	ad = {0, 0, -20001, 0}
	double		radius = 20001;
}			t_north;

typedef struct		s_square_south
{
	t_point		o = {0, 0, 0, -10000};
	t_vector	normal = {0, 0, 0, 1};
	t_point		a = {0, 10000, 10000, -10000};
	t_vector	ab = {0, -20001, 0, 0};
	t_vector	ad = {0, 0, -20001, 0}
	double		radius = 20001;
}			t_south;

typedef struct		s_square_east
{
	t_point		o = {0, -10000, 0, 0};
	t_vector	normal = {0, -1, 0, 0};
	t_point		a = {0, -10000, 10000, -10000};
	t_vector	ab = {0, 0, 0, 20001};
	t_vector	ad = {0, 0, -20001, 0}
	double		radius = 20001;
}			t_east;

typedef struct		s_square_west
{
	t_point		o = {0, 10000, 0, 0};
	t_vector	normal = {0, 1, 0, 0};
	t_point		a = {0, 10000, 10000, 10000};
	t_vector	ab = {0, 0, 0, -20001};
	t_vector	ad = {0, 0, -20001, 0}
	double		radius = 20001;
}			t_west;
