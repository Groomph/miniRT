/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2020/12/21 18:41:52 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "window_camera.h"
#include <stdio.h>

void	ray_caster(t_cam *cam, t_vector *ray_dir, long double pct_w, long double pct_h)
{
	ray_dir->x = cam->lower_corner.x 
		+ cam->horizontal.x * pct_w
		+ cam->vertical.x * pct_h
		- cam->origin.x;       
	ray_dir->y = cam->lower_corner.y
		+ cam->horizontal.y * pct_w
		+ cam->vertical.y * pct_h
		- cam->origin.y;       
	ray_dir->z = cam->lower_corner.z
		+ cam->horizontal.z * pct_w
		+ cam->vertical.z * pct_h
		- cam->origin.z;
//		printf("%%w: %Lf\n", pct_w);
//		printf("%%h: %Lf\n", pct_h);
//		printf("ray x: %Lf\n", ray_dir->x);
//		printf("ray y: %Lf\n", ray_dir->y);
//		printf("ray z: %Lf\n", ray_dir->z);
	//	scanf("%c", test);	
}

int	main(void)
{
	void	*mlx_ptr;
	void	*window_ptr;
	t_img	img;
	t_cam	cam;

	mlx_ptr = mlx_init();
	init_window_img(&img, &mlx_ptr, &window_ptr);
	init_camera(&img, &cam);

	int	x;
	int	y;

	x = 0;
	y = 0;

/*	t_sphere sphere;
	sphere.origin.x = -(cos(PI/4));
	sphere.origin.y = 0;
	sphere.origin.z = -1.0;
	sphere.radius = cos(PI/4);

	t_sphere sphere2;
	sphere2.origin.x = cos(PI/4);
	sphere2.origin.y = 0.0;
	sphere2.origin.z = -1.0;
	sphere2.radius = cos(PI/4);
*/	
	t_sphere sphere;
	sphere.origin.x = 0;
	sphere.origin.y = 0;
	sphere.origin.z = -1.0;
	sphere.radius = 0.5;

	t_sphere sphere2;
	sphere2.origin.x = -1.0;
	sphere2.origin.y = 0;
	sphere2.origin.z = -1.0;
	sphere2.radius = 0.5;

	t_sphere sphere3;
	sphere3.origin.x = 1.0;
	sphere3.origin.y = 0;
	sphere3.origin.z = -1.0;
	sphere3.radius = 0.5;
	
	t_sphere sphere4;
	sphere4.origin.x = 0.0;
	sphere4.origin.y = -1000.5;
	sphere4.origin.z = 0;
	sphere4.radius = 1000.0;

	t_vector ray_direction;

	while (y < img.col_h)
	{
		while (x < img.line_w)
		{
			ray_caster(&cam, &ray_direction, 1.0 - (double)x / (double)(img.line_w - 1),
							1.0 - (double)y / (double)(img.col_h - 1));
			if (is_intercept_sphere(&(cam.origin), &ray_direction, &sphere4))
				img.addr[y * img.line_w + x] = 0x0000FF00;
			if (is_intercept_sphere(&(cam.origin), &ray_direction, &sphere3))
				img.addr[y * img.line_w + x] = 0x00FF0000;
			if (is_intercept_sphere(&(cam.origin), &ray_direction, &sphere))
				img.addr[y * img.line_w + x] = 0x000000FF;
			if (is_intercept_sphere(&(cam.origin), &ray_direction, &sphere2))
				img.addr[y * img.line_w + x] = 0x00FF00FF;
			x++;
		}
		y++;
		x = 0;
	}
	printf("Rendering done\n");
	mlx_put_image_to_window(mlx_ptr, window_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (1);
}
