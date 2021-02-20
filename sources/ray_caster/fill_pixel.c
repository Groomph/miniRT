/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/02/20 02:57:52 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <math.h>
#include <pthread.h>
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

void		end_thread(t_scene *scene, t_thread *thread)
{
//	if (scene->thread_on == 1)
	if (thread->id == 0)
	{
	//	scene->thread_on--;
		printf("Rendering done\n");
		printf("ESCAPE = quit miniRT\nENTER = launch render\n");
		printf("- = decrease move speed and rotation\n");
		printf("+ = increase move speed and rotation\n");
		printf("R = decrease number of render thread\n");
		printf("T = increase number of render thread\n");
		printf("A, E, ARROWS = rotate the camera or the selected object\n");
		printf("Z, Q, S, D, CTRL, SPACE = move the camera or the selected object\n");
		printf("LEFT CLICK = move the camera\n");
		printf("RIGHT CLICK = select the object\n");
		printf("TAB = deselect object if selected\n");
	}
//	else
//		scene->thread_on--;
	scene = NULL;
//	pthread_detach(scene->tab_thread[thread->id]);
//	free(thread);
//	pthread_attr_destroy(&scene->attr_thread[thread->id]);
	pthread_exit(NULL);
}

void		*ray_caster(void *temp_thread)
{
	t_scene	*scene;
	t_thread *thread;
	t_ray	ray;
	int		x;
	int		count;
	int		count_range;
	int		max_count;

	thread = (t_thread*)temp_thread;
	scene = thread->scene;
	count = thread->max_y - thread->y;
	count_range = count / 20;
	max_count = thread->y + count_range;
	count = 0;
	while (thread->y < thread->max_y)
	{
		x = -1;
		while (++x < scene->img.line_w)
			scene->img.addr[thread->pixel++] =
				fill_pixel(scene, &ray, x, thread->y);
		while (thread->id == 1 && thread->y > max_count && ++count < 20)
		{
			printf("Rendering: %d%%\n", count * 5);
			max_count += count_range;
		}
		thread->y++;
	}
	end_thread(scene, thread);
	return (NULL);
}
