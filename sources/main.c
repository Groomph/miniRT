/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/02/19 22:21:15 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	set_window_img(t_scene *scene, void *mlx, void **window)
{
	if (!scene->saveit)
		*window = mlx_new_window(mlx, scene->img.line_w,
						scene->img.col_h, "miniRT");
	scene->img.img = mlx_new_image(mlx, scene->img.line_w,
							scene->img.col_h);
	scene->img.addr = (int*)mlx_get_data_addr(scene->img.img,
	&(scene->img.bits_pixel), &(scene->img.line_w), &(scene->img.endian));
	scene->img.line_w /= 4;
}

int			update(t_scene *scene)
{
	if (scene->thread_on == 0)
		mlx_put_image_to_window(scene->mlx, scene->window,
							scene->img.img, 0, 0);
	return (1);
}

int			main(int ac, char **av)
{
	t_scene	scene;

	init_zero(&scene, sizeof(scene));
	scene.mlx = mlx_init();
	check_prog_args(&scene, &(scene.img), ac, av);
	set_window_img(&scene, scene.mlx, &(scene.window));
	scene.thread_on = 0;
	launch_threads(&scene);
	if (scene.saveit)
		create_bmp(&scene, &(scene.img));
	//mlx_do_key_autorepeatoff(scene.mlx);
	mlx_hook(scene.window, 2, (1L << 0), press_key, &scene);
	mlx_hook(scene.window, 33, (1L << 17), stop_program, &scene);
	mlx_hook(scene.window, 4, (1L << 2), press_mouse_button, &scene);
	mlx_loop_hook(scene.mlx, update, &scene);
	mlx_loop(scene.mlx);
	return (1);
}
