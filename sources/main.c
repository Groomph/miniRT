/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/14 17:34:55 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <stdio.h>

void	ray_caster(t_cam *cam, t_vector *ray_dir, long double pct_w, long double pct_h)
{
	t_vector temp;
	
	temp = multiply_vector(&(cam->horizontal), pct_w);
	*ray_dir = add_vectors(&(cam->lower_corner), &temp);
	temp = multiply_vector(&(cam->vertical), pct_h);
	*ray_dir = add_vectors(ray_dir, &temp);
	*ray_dir = subtract_vectors(ray_dir, &(cam->origin));
//	get_normalized(ray_dir);

//		printf("%%w: %Lf\n", pct_w);
//		printf("%%h: %Lf\n", pct_h);
//		printf("ray x: %Lf\n", ray_dir->x);
//		printf("ray y: %Lf\n", ray_dir->y);
//		printf("ray z: %Lf\n", ray_dir->z);
	//	scanf("%c", test);	
}

int		is_intercept_object(t_scene *scene, t_vector *ray_dir)
{
	t_list	*temp;
	t_obj	*temp_obj;

	temp = scene->object;
	while (temp)
	{
		temp_obj = temp->object;
		if (temp_obj->f(scene->active_cam, ray_dir, &(temp_obj->data)))
			return (temp_obj->color);
		temp = temp->next;
	}
	return (0);
}


void            init_window_img(t_img *img, void **mlx_ptr, void **window_ptr)
{
        *window_ptr = mlx_new_window(*mlx_ptr, img->line_w, img->col_h, "test");
        img->img = mlx_new_image(*mlx_ptr, img->line_w, img->col_h);
        img->addr = (int*)mlx_get_data_addr(img->img, &(img->bits_pixel),
                        &(img->line_w), &(img->endian));
        img->line_w /= 4;
}


int	main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*window_ptr;
	t_scene	scene;
	int	x;
	int	y;
	t_vector ray_direction;

	x = 0;
	y = 0;
	init_zero(&scene, sizeof(scene));
	check_prog_args(&scene, ac, av);
	mlx_ptr = mlx_init();
	init_window_img(&(scene.img), &mlx_ptr, &window_ptr);
	while (y < scene.img.col_h)
	{
		while (x < scene.img.line_w)
		{
			ray_caster(scene.active_cam, &ray_direction,
				1 - (double)x / (double)(scene.img.line_w - 1),
				1 - (double)y / (double)(scene.img.col_h - 1));
			scene.img.addr[y * scene.img.line_w + x] = is_intercept_object(&scene, &ray_direction);
			x++;
		}
		y++;
		x = 0;
	}
	printf("Rendering done\n");
	mlx_put_image_to_window(mlx_ptr, window_ptr, scene.img.img, 0, 0);
	mlx_loop(mlx_ptr);
	stop_program(&scene, 0, 0);
	return (1);
}
