/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/02/18 04:14:37 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <math.h>
#include <stdio.h>

void	set_ray(t_scene *scene, t_ray *ray, double x, double y)
{
	t_point		x_pos;
	t_point		y_pos;

	ray->o = scene->cam->o;
	x = 1 - x / (scene->img.line_w - 1);
	y = 1 - y / (scene->img.col_h - 1);
	x_pos = multiply_vector(&(scene->cam->horizontal), x);
	ray->dir = add_vectors(&(scene->cam->lower_corner), &x_pos);
	y_pos = multiply_vector(&(scene->cam->vertical), y);
	ray->dir = add_vectors(&(ray->dir), &y_pos);
	ray->dir = sub_vectors(&(ray->dir), &(scene->cam->o));
	set_normalized(&(ray->dir));
	ray->t = 1000000;
	ray->color = get_vector(0, 0, 0, 0);
}

static void		pixel_correction(t_cam *cam, t_color *color)
{
	color->x /= cam->anti_aliasing * cam->anti_aliasing;
	color->y /= cam->anti_aliasing * cam->anti_aliasing;
	color->z /= cam->anti_aliasing * cam->anti_aliasing;
	if (cam->gamma)
	{
		color->x = pow(color->x * 70, 1 / 1.9);
		color->y = pow(color->y * 70, 1 / 1.9);
		color->z = pow(color->z * 70, 1 / 1.9);
	}
}

static int		fill_pixel(t_scene *scene, t_ray *ray, double x, double y)
{
	int		i;
	int		j;
	t_color	temp_color;

	temp_color = get_vector(0, 0, 0, 0);
	i = -1;
	while (++i < scene->cam->anti_aliasing)
	{
		j = -1;
		while (++j < scene->cam->anti_aliasing)
		{
			set_ray(scene, ray,
			x + (double)i / scene->cam->anti_aliasing,
			y + (double)j / scene->cam->anti_aliasing);
			path_tracer(scene, ray, 0);
			temp_color.x += ray->color.x;
			temp_color.y += ray->color.y;
			temp_color.z += ray->color.z;
		}
	}
	pixel_correction(scene->cam, &temp_color);
	return (fuse_vector(&(temp_color)));
}

void		ray_caster(t_scene *scene, void *mlx, void *window)
{
	t_ray	ray;
	int		x;
	int		y;
	int		pixel;
	int		count[3];

	y = -1;
	pixel = 0;
	count[2] = (scene->img.col_h / 20) + 1;
	count[1] = count[2];
	count[0] = 1;
	while (++y < scene->img.col_h)
	{
		x = -1;
		while (++x < scene->img.line_w)
			scene->img.addr[pixel++] = fill_pixel(scene, &ray, x, y);
		while (y > count[1])
		{
			printf("Rendering: %d%%\n", 5 * count[0]++);
			count[1] += count[2];
		}
	}
	if (!scene->saveit)
		mlx_put_image_to_window(mlx, window, scene->img.img, 0, 0);
	printf("Rendering done\n");
}
