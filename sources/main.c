/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/21 05:11:01 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"

static void	set_window_img(t_img *img, void *mlx, void **window)
{
	*window = mlx_new_window(mlx, img->line_w, img->col_h, "test");
	img->img = mlx_new_image(mlx, img->line_w, img->col_h);
	img->addr = (int*)mlx_get_data_addr(img->img, &(img->bits_pixel),
					&(img->line_w), &(img->endian));
	img->line_w /= 4;
}

int			main(int ac, char **av)
{
	void	*mlx;
	void	*window;
	t_scene	scene;
	t_img	img;

	init_zero(&scene, sizeof(scene));
	init_zero(&img, sizeof(img));
	check_prog_args(&scene, &img, ac, av);
	mlx = mlx_init();
	set_window_img(&img, mlx, &window);
	ray_caster(&scene, &img, mlx, window);
	mlx_loop(mlx);
	stop_program(&scene, 0, 0);
	return (1);
}

/*
**Ajouter une condition de parsing fausse quand cam.o == cam.look_at
*/
