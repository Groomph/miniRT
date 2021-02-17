/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:03:48 by romain            #+#    #+#             */
/*   Updated: 2021/02/11 21:26:16 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bmp.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void	set_headers(t_img *img, t_bmp *bmp)
{
	bmp->header.signature1 = 'B';
	bmp->header.signature2 = 'M';
	bmp->header.file_size_bytes = 54 + 4 * img->line_w * img->col_h;
	bmp->header.reserved1 = 0;
	bmp->header.reserved2 = 0;
	bmp->header.offset_img_begin = 54;
	bmp->img.signature = 40;
	bmp->img.img_width_pixels = img->line_w;
	bmp->img.img_height_pixels = img->col_h;
	bmp->img.planes = 1;
	bmp->img.bits_per_pixel = 32;
	bmp->img.compression = 0;
	bmp->img.img_size_bytes = 4 * img->line_w * img->col_h;
	bmp->img.hori_resolution = img->line_w;
	bmp->img.vert_resolution = img->col_h;
	bmp->img.pallet_color_nb = 0xffffffff;
	bmp->img.important_color_nb = 0;
}

void		create_bmp(t_scene *scene, t_img *img)
{
	int		fd;
	t_bmp	bmp;
	int		i;
	int		j;

	set_headers(img, &bmp);
	fd = open("img.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(fd, &(bmp.header.signature1), 10);
	write(fd, &(bmp.header.offset_img_begin), 4);
	write(fd, &(bmp.img.signature), 36);
	write(fd, &(bmp.img.important_color_nb), 4);
	i = img->col_h;
	while (--i >= 0)
	{
		j = -1;
		while (++j < img->line_w)
		{
			write(fd, &(img->addr[i * img->line_w + j]), 4);
		}
	}
	close(fd);
	stop_program(scene);
}
