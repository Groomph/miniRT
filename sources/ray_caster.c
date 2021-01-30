/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/29 22:04:05 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <math.h>
#include <stdio.h>

static t_vector	get_ray_dir(t_cam *cam, t_img *img, double x, double y)
{
	t_vector	dir;
	t_point		x_pos;
	t_point		y_pos;

	x = 1 - x / (img->line_w - 1);
	y = 1 - y / (img->col_h - 1);
	x_pos = multiply_vector(&(cam->horizontal), x);
	dir = add_vectors(&(cam->lower_corner), &x_pos);
	y_pos = multiply_vector(&(cam->vertical), y);
	dir = add_vectors(&dir, &y_pos);
	dir = sub_vectors(&dir, &(cam->o));
	set_normalized(&dir);
	return (dir);
}

static int		fill_pixel(t_scene *scene, t_ray *ray, double x, double y)
{
	int		alias;
	int		i;
	int		j;
	t_color	temp_color;

	temp_color = get_vector(0, 0, 0, 0);
	alias = 1;
	i = -1;
	while (++i < alias)
	{
		j = -1;
		while (++j < alias)
		{
			ray->o = scene->cam->o;
			ray->dir = get_ray_dir(scene->cam, &(scene->img),
			x + (double)i / alias, y + (double)j / alias);
			path_tracer(scene, ray, NULL, 0);
			temp_color.x += ray->color.x;
			temp_color.y += ray->color.y;
			temp_color.z += ray->color.z;
		}
	}
	temp_color.x /= alias * alias;
	temp_color.y /= alias * alias;
	temp_color.z /= alias * alias;
	return (fuse_vector(&(temp_color)));
}

/*
**	ray->color.x = pow(ray->color.x, 1 / 2.0);
**	ray->color.y = pow(ray->color.y, 1 / 2.0);
**	ray->color.z = pow(ray->color.z, 1 / 2.0);
*/

static void	display_progress(double pixel, t_img *img, double *count)
{
	if (*count < pixel / (img->line_w * img->col_h))
	{
		printf("Rendering: %d%%\n", (int)(*count * 100));
		*count += 0.05;
	}
}

void		ray_caster(t_scene *scene, void *mlx, void *window)
{
	t_ray	ray;
	int		x;
	int		y;
	int		pixel;
	double	count;

	y = -1;
	pixel = 0;
	count = 0.05;
	while (++y < scene->img.col_h)
	{
		x = -1;
		while (++x < scene->img.line_w)
		{
			scene->img.addr[pixel] = fill_pixel(scene, &ray, x, y);
			display_progress(pixel, &(scene->img), &count);
			pixel++;
		}
	}
	mlx_put_image_to_window(mlx, window, scene->img.img, 0, 0);
	printf("Rendering done\n");
}

/*
**	if (i < alias / 4)
**	{
**		randomx = (double)i / (alias / 4) * -1;
**		randomy = (double)i / (alias / 4);
**	}
**	if (i < alias / 2)
**	{
**		randomx = ((double)i - (alias / 4)) / (alias / 4) * -1;
**		randomy = ((double)i - (alias / 4)) / (alias / 4) * -1;
**	}
**	if (i < alias / 2 / 2)
**	{
**		randomx = ((double)i - (alias / 2)) / (alias / 4);
**		randomy = ((double)i - (alias / 2)) / (alias / 4) * -1;
**	}
**	if (i < alias)
**	{
**		randomx = ((double)i - (alias / 2 + alias / 4)) / (alias / 4);
**		randomy = ((double)i - (alias / 2 + alias / 4)) / (alias / 4);
**	}
*/
