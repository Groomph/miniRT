/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/21 18:38:12 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "window_camera.h"
#include <math.h>

void		init_window_img(t_img *img, void **mlx_ptr, void **window_ptr)
{
	img->line_w = 1024;
	img->col_h = 512;

	*window_ptr = mlx_new_window(*mlx_ptr, img->line_w, img->col_h, "test");
	img->img = mlx_new_image(*mlx_ptr, img->line_w, img->col_h);
	img->addr = (int*)mlx_get_data_addr(img->img, &(img->bits_pixel),
			&(img->line_w), &(img->endian));
	img->line_w /= 4;
	printf("win_w: %d\n", img->line_w);
	printf("win_h: %d\n", img->col_h);
}
static void	init_camera2(t_img *img, t_cam *cam)
{
	t_vector w;
	w = subtract_vectors(&(cam->origin), &(cam->look_at));
	get_normalized(&w);

printf("%lf\n", w.x);
printf("%lf\n", w.y);
printf("%lf\n", w.z);
	t_vector u; //handle rotation
	u.x = 0.0;
	u.y = 1.0;
	u.z = 0.0;
	u = get_vector_product(&u, &w);
	get_normalized(&u);

	t_vector v;
	v = get_vector_product(&w, &u);
	cam->horizontal.x = cam->pov_w * u.x;
	cam->horizontal.y = cam->pov_w * u.y;
	cam->horizontal.z = cam->pov_w * u.z;
	cam->vertical.x = cam->pov_h * v.x;
	cam->vertical.y = cam->pov_h * v.y;
	cam->vertical.z = cam->pov_h * v.z;
	cam->lower_corner.x = cam->origin.x - (cam->horizontal.x / 2.0)
		- (cam->vertical.x / 2.0) - w.x;
	cam->lower_corner.y = cam->origin.y - (cam->horizontal.y / 2.0)
		- (cam->vertical.y / 2.0) - w.y;
	cam->lower_corner.z = cam->origin.z - (cam->horizontal.z / 2.0)
		- (cam->vertical.z / 2.0) - w.z;
}

void		init_camera(t_img *img, t_cam *cam)
{
	cam->origin.x = -2.0;
	cam->origin.y = 2.0;
	cam->origin.z = 1.0;

	cam->look_at.x = 0.0;
	cam->look_at.y = 0.0;
	cam->look_at.z = -1.0;

	cam->fov_ver = 90 * PI / 180;
	cam->fov_ver = tan(cam->fov_ver / 2);

	cam->pov_h = 2.0 * cam->fov_ver;
	cam->ratio = (double)img->line_w / (double)img->col_h;
	cam->pov_w = cam->pov_h * cam->ratio;

	init_camera2(img, cam);

	printf("pov_w: %lf\n", cam->pov_w);
	printf("pov_h: %lf\n", cam->pov_h);
	printf("ratio: %lf\n", cam->ratio);
	printf("lower point x: %lf\n", cam->lower_corner.x);
	printf("lower point y: %lf\n", cam->lower_corner.y);
	printf("lower point z: %lf\n", cam->lower_corner.z);
}
