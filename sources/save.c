/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:03:48 by romain            #+#    #+#             */
/*   Updated: 2021/02/11 18:38:35 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bmp.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void	set_headers(t_scene *scene, t_bmp *bmp)
{
	bmp->header.signature[0] = 'B';
	bmp->header.signature[1] = 'M';
	bmp->header.file_size_bytes = 54 +
				4 * scene->img.line_w * scene->img.col_h;
	bmp->header.reserved1 = 0;
	bmp->header.reserved2 = 0;
	bmp->header.offset_img_begin = 54;
	bmp->img.signature = 40;
	bmp->img.img_width_pixels = scene->img.line_w;
	bmp->img.img_height_pixels = scene->img.col_h;
	bmp->img.planes = 1;
	bmp->img.bits_per_pixel = 32;
	bmp->img.compression = 0;
	bmp->img.img_size_bytes = 4 * scene->img.line_w * scene->img.col_h;
	bmp->img.hori_resolution = scene->img.line_w;
	bmp->img.vert_resolution = scene->img.col_h;
	bmp->img.pallet_color_nb = 0xffffff;
	bmp->img.important_color_nb = 0;
}

void	create_bmp(t_scene *scene)
{
	int	fd;
	t_bmp	bmp;
	int	i;
	int	j;

	set_headers(scene, &bmp);
	fd = open("img.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("%ld\n", sizeof(bmp));
	write(fd, &(bmp.header), 14);
	write(fd, &(bmp.img), 40);
	i = scene->img.col_h;
	while (--i >= 0)
	{
		j = -1;
		while (++j < scene->img.line_w)
			write(fd, &(scene->img.addr[i * scene->img.line_w + j]), 4);
	}
	close(fd);
	stop_program(scene);
}
