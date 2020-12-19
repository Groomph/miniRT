/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2020/12/19 12:31:23 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vector.h"
#include "minirt.h"
#include <stdio.h>
#include <math.h>

typedef struct		s_img {
	void		*img;
	int		*addr;
	int		line_w;
	int		col_h;
	int		h;
	int		bits_pixel;
	int		endian;
}			t_img;

int	build_color(int a, int r, int g, int b)
{
	/*
	unsigned int	temp;

	temp = 0;
	temp |= a << 24;
	printf("%u_\n", temp);
	temp |= r << 16;
	printf("%u_\n", temp);
	temp |= g << 8;
	printf("%u_\n", temp);
	temp |= b;
	printf("%u_\n", temp);
*/
	return (a << 24 | r << 16 | g << 8 | b);
}

void	colorful_background(t_img img)
{
	int		x;
	int 		y;
	long double 		cr;
	long double		cg;
	long double		cb;

	x = 0;
	y = 0;
	while (y < img.col_h)
	{
		while (x < img.line_w)
		{
	//		printf("x: %d\n", x);
	//		printf("y: %d\n", y);
			cg = (y + 1) / (double)(img.col_h); 
			cb = (x + 1) / (double)(img.line_w);
//	cb = ((double)((x / 2) + y + 2.0) / ((img.line_w / 2) + img.col_h)) - 1.0;
			if (cg < cb)
				cr = cb;
			else
				cr = cg;
			cr = (cr - 1.0) * -1;
		//	printf("red:   %Lf\n", cr);
		//	printf("green: %Lf\n", cg);
		//	printf("blue:  %Lf\n", cb);
			if (cb < 0.0)
				cb *= -1;
			img.addr[x + (y * img.line_w)] =
				build_color(0x0, cr * 255, cg * 255, cb * 255);
			x++;
		}
		y++;
		x = 0;
	}

}

void	init_window_img(t_img *img, void **mlx_ptr, void **window_ptr)
{
	img->line_w = 768;
	img->col_h = 512;
	*window_ptr = mlx_new_window(*mlx_ptr, img->line_w, img->col_h, "test");
	img->img = mlx_new_image(*mlx_ptr, img->line_w, img->col_h);
	img->addr = (int*)mlx_get_data_addr(img->img, &(img->bits_pixel),
			&(img->line_w), &(img->endian));
	img->line_w /= 4;
}

typedef struct		s_sphere
{
	t_vector	origin;
	int		diameter;
}			t_sphere;

BOOL	is_intercept(t_vector *ray_o, t_vector *ray_dir, t_sphere *sphere)
{
	long double	a;
	long double	b;
	long double	c;
	long double	delta;

	t_vector temp;
       	temp = subtract_vectors(ray_o, &(sphere->origin));
	
	a = 1.0;
	b = 2.0 * get_scalar_product(ray_dir, &temp);
	c = get_norme(&temp) - sphere->diameter * sphere->diameter;
	delta = b * b - 4 * a * c;
	if (delta < 0.0)
		return (FALSE);
	long double t1;
	long double t2;

	t1 = (-b - sqrt(delta)) / (2.0 * a);
	t2 = (-b + sqrt(delta)) / (2.0 * a);
	if (t2 > 0.0)
		return (TRUE);
	return (FALSE);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*window_ptr;
	t_img	img;

	mlx_ptr = mlx_init();
	init_window_img(&img, &mlx_ptr, &window_ptr);

	colorful_background(img);

	int	x;
	int	y;

	x = 0;
	y = 0;

	t_sphere sphere;
	sphere.origin.x = -50;
	sphere.origin.y = -50;
	sphere.origin.z = -150;
	sphere.diameter = 20;

	t_vector ray_origin;
	ray_origin.x = 0;
	ray_origin.y = 0;
	ray_origin.z = 0;
	
	t_sphere sphere2;
	sphere2.origin.x = 47000;
	sphere2.origin.y = 0;
	sphere2.origin.z = -40000;
	sphere2.diameter = 46000;

	
	long double	f_o_v;
	f_o_v = 60 * PI / 180;
	printf("%Lf\n", f_o_v);
	int	color;
	color = build_color(0x0, 0x0, 0x0, 0x0);
	
	t_vector ray_direction;
	while (y < img.col_h)
	{
		while (x < img.line_w)
		{
			ray_direction.x = x - (img.line_w / 2.0);
			ray_direction.y = y - (img.col_h / 2.0);
			ray_direction.z = (-img.line_w) / (2.0 * tan(f_o_v / 2.0));
			get_normalized(&ray_direction);
	
			if (is_intercept(&ray_origin, &ray_direction, &sphere) ||
				is_intercept(&ray_origin, &ray_direction, &sphere2))
			{
			}
			else
				img.addr[y * img.line_w + x] = color;

			x++;
		}
		y++;
		x = 0;
	}
/*
	x = 0;
	y = 0;

	while (y < img.col_h)
	{
		while (x < img.line_w)
		{
			ray_direction.x = x - (img.line_w / 2);
			ray_direction.y = y - (img.col_h / 2);
			ray_direction.z = -img.line_w / (2 * tan(f_o_v / 2));
			get_normalized(&ray_direction);
	
			if (!is_intercept(&ray_origin, &ray_direction, &sphere2))
				img.addr[y * img.line_w + x] = 0x0;

//			printf("direction x: %Lf\n", ray_dir.x);
//			printf("direction y: %Lf\n", ray_dir.y);
//			printf("direction z: %Lf\n", ray_dir.z);
			x++;
		}
		y++;
		x = 0;
	}

	x = 0;
	y = 0;
	sphere.origin.x = -50;
	sphere.origin.y = -50;
	sphere.origin.z = -150;
	sphere.diameter = 20;

	while (y < img.col_h)
	{
		while (x < img.line_w)
		{
			ray_direction.x = x - (img.line_w / 2.0);
			ray_direction.y = y - (img.col_h / 2.0);
			ray_direction.z = (-img.line_w) / (2.0 * tan(f_o_v / 2.0));
			get_normalized(&ray_direction);
	
			if (is_intercept(&ray_origin, &ray_direction, &sphere))
				img.addr[y * img.line_w + x] = 0x00505050;

			x++;
		}
		y++;
		x = 0;
	}
*/
	mlx_put_image_to_window(mlx_ptr, window_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (1);
}
