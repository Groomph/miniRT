/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/21 04:49:38 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <stdio.h>

void		apply_light(t_ray *ray)
{
	double		light_intensity;
	t_point		light_pos;
	t_vector	rev_lightray;
	t_vector	normed_rev_lightray;
	double		cos;

	light_intensity = 100;
	light_pos = get_vector(0, 0, 3, -5);
	rev_lightray = sub_vectors(&light_pos, &(ray->hit));
	normed_rev_lightray = rev_lightray;
	set_normalized(&normed_rev_lightray);
	cos = get_scalar_product(&normed_rev_lightray, &(ray->hit_normale));
	if (cos <= 0)
	{
		ray->color = get_vector(0, 0, 0, 0);
		return ;
	}
	light_intensity *= cos;
	light_intensity /= get_norme(&rev_lightray);
	ray->color.other *= light_intensity;
	ray->color = multiply_vector(&(ray->color), light_intensity);
}

static int		find_nearest_object(t_scene *scene, t_ray *ray)
{
	t_list	*temp;
	t_obj	*temp_obj;
	t_color	*temp_color;

	ray->max_t = 50;
	temp_color = NULL;
	temp = scene->object;
	while (temp)
	{
		temp_obj = temp->object;
		if (temp_obj->f(ray, &(temp_obj->data)))
		{
			ray->max_t = ray->t[0];
			temp_color = &(temp_obj->color);
		}
		temp = temp->next;
	}
	if (!temp_color)
		return (FALSE);
	ray->color = *temp_color;
	return (TRUE);
}

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
	set_normalized(&(dir));
	return (dir);
}

void		ray_caster(t_scene *scene, t_img *img, void *mlx, void *window)
{
	t_ray	ray;
	int		x;
	int		y;

	ray.o = scene->cam->o;
	x = 0;
	y = 0;
	ray.pixel = 0;
	while (y < img->col_h)
	{
		while (x < img->line_w)
		{
			ray.dir = get_ray_dir(scene->cam, img, x, y);
			ray.color = get_vector(0, 0, 0, 0);
			if (find_nearest_object(scene, &ray))
				apply_light(&ray);
			img->addr[ray.pixel] = fuse_vector(&(ray.color));
			x++;
			ray.pixel++;
		}
		y++;
		x = 0;
	}
	mlx_put_image_to_window(mlx, window, img->img, 0, 0);
	printf("Rendering done\n");
}
