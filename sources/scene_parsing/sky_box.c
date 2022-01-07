/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 05:08:57 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 16:48:20 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	set_square2(t_scene *scene)
{
	scene->skybox[4].o = get_vector(0, -512, 0, 0);
	scene->skybox[4].normal = get_vector(0, -1, 0, 0);
	scene->skybox[4].a = get_vector(0, -512, 512, -512);
	scene->skybox[4].ab = get_vector(0, 0, 0, 1024);
	scene->skybox[4].ad = get_vector(0, 0, -1024, 0);
	scene->skybox[4].radius = 1024;
	scene->skybox[5].o = get_vector(0, 512, 0, 0);
	scene->skybox[5].normal = get_vector(0, 1, 0, 0);
	scene->skybox[5].a = get_vector(0, 512, 512, 512);
	scene->skybox[5].ab = get_vector(0, 0, 0, -1024);
	scene->skybox[5].ad = get_vector(0, 0, -1024, 0);
	scene->skybox[5].radius = 1024;
	scene->box = TRUE;
}

void	set_square(t_scene *scene)
{
	scene->skybox[0].o = get_vector(0, 0, 512, 0);
	scene->skybox[0].normal = get_vector(0, 0, 1, 0);
	scene->skybox[0].a = get_vector(0, -512, 512, 512);
	scene->skybox[0].ab = get_vector(0, 1024, 0, 0);
	scene->skybox[0].ad = get_vector(0, 0, 0, -1024);
	scene->skybox[0].radius = 1024;
	scene->skybox[1].o = get_vector(0, 0, -512, 0);
	scene->skybox[1].normal = get_vector(0, 0, -1, 0);
	scene->skybox[1].a = get_vector(0, -512, -512, 512);
	scene->skybox[1].ab = get_vector(0, 1024, 0, 0);
	scene->skybox[1].ad = get_vector(0, 0, 0, -1024);
	scene->skybox[1].radius = 1024;
	scene->skybox[2].o = get_vector(0, 0, 0, 512);
	scene->skybox[2].normal = get_vector(0, 0, 0, 1);
	scene->skybox[2].a = get_vector(0, -512, 512, 512);
	scene->skybox[2].ab = get_vector(0, 1024, 0, 0);
	scene->skybox[2].ad = get_vector(0, 0, -1024, 0);
	scene->skybox[2].radius = 1024;
	scene->skybox[3].o = get_vector(0, 0, 0, -512);
	scene->skybox[3].normal = get_vector(0, 0, 0, -1);
	scene->skybox[3].a = get_vector(0, 512, 512, -512);
	scene->skybox[3].ab = get_vector(0, -1024, 0, 0);
	scene->skybox[3].ad = get_vector(0, 0, -1024, 0);
	scene->skybox[3].radius = 1024;
	set_square2(scene);
}

BOOL	add_sky_box2(t_sky_box *box)
{
	int	i;
	int	t[3];

	i = -1;
	while (++i < 6)
		if (box[i].img == NULL)
			return (FALSE);
	box[0].addr = (int *)mlx_get_data_addr(box[0].img,
			&t[0], &t[1], &t[2]);
	box[1].addr = (int *)mlx_get_data_addr(box[1].img,
			&t[0], &t[1], &t[2]);
	box[2].addr = (int *)mlx_get_data_addr(box[2].img,
			&t[0], &t[1], &t[2]);
	box[3].addr = (int *)mlx_get_data_addr(box[3].img,
			&t[0], &t[1], &t[2]);
	box[4].addr = (int *)mlx_get_data_addr(box[4].img,
			&t[0], &t[1], &t[2]);
	box[5].addr = (int *)mlx_get_data_addr(box[5].img,
			&t[0], &t[1], &t[2]);
	return (TRUE);
}

BOOL	add_sky_box(t_scene *scene, char *format)
{
	int			i;
	t_sky_box	*box;

	i = 6;
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	set_square(scene);
	box = scene->skybox;
	box[0].img = mlx_xpm_file_to_image(scene->mlx, "box/top.xpm",
			&(box[0].w), &(box[0].h));
	box[1].img = mlx_xpm_file_to_image(scene->mlx, "box/bot.xpm",
			&(box[1].w), &(box[1].h));
	box[2].img = mlx_xpm_file_to_image(scene->mlx, "box/north.xpm",
			&(box[2].w), &(box[2].h));
	box[3].img = mlx_xpm_file_to_image(scene->mlx, "box/south.xpm",
			&(box[3].w), &(box[3].h));
	box[4].img = mlx_xpm_file_to_image(scene->mlx, "box/east.xpm",
			&(box[4].w), &(box[4].h));
	box[5].img = mlx_xpm_file_to_image(scene->mlx, "box/west.xpm",
			&(box[5].w), &(box[5].h));
	if (!add_sky_box2(box))
		return (FALSE);
	return (TRUE);
}
