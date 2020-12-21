/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_camera.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/21 18:20:15 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_CAMERA_H
# define WINDOW_CAMERA_H

# include "vector.h"

typedef struct		s_window_image
{
	void		*img;
	int		*addr;
	int		line_w;
	int		col_h;
	int		bits_pixel;
	int		endian;
}			t_img;

typedef struct		s_camera
{
	t_vector	origin;
	t_vector	look_at;
	double		fov_ver;
	double		pov_w;
	double		pov_h;
	double		ratio;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	lower_corner;
}			t_cam;

void			init_camera(t_img *img, t_cam *cam);
void			init_window_img(t_img *img, void **mlx_ptr, void **window_ptr);

#endif
