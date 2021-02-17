/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:46:34 by romain            #+#    #+#             */
/*   Updated: 2021/02/11 20:44:10 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

typedef struct	s_file_header
{
	char		signature1;
	char		signature2;
	int		file_size_bytes;
	short		reserved1;
	short		reserved2;
	int		offset_img_begin;
}			t_file_h;

typedef struct		s_img_header
{
	int		signature;
	int		img_width_pixels;
	int		img_height_pixels;
	short		planes;
	short		bits_per_pixel;
	int		compression;
	int		img_size_bytes;
	int		hori_resolution;
	int		vert_resolution;
	int		pallet_color_nb;
	int		important_color_nb;
}			t_img_h;

typedef struct		s_bmp
{
	t_file_h	header;
	t_img_h		img;
}			t_bmp;

#endif
