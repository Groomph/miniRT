#include "mlx.h"
#include "vector.h"

#include <stdio.h>

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

void	add_sphere(int x, int y, int ray, int color)
{

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
			printf("x: %d\n", x);
			printf("y: %d\n", y);
			cr = (y + 1) / (double)(img.col_h); 
			cg = (x + 1) / (double)(img.line_w);
//	cb = ((double)((x / 2) + y + 2.0) / ((img.line_w / 2) + img.col_h)) - 1.0;
			if (cr < cg)
				cb = cg;
			else
				cb = cr;
			cb = (cb - 1.0) * -1;
			printf("red:   %Lf\n", cr);
			printf("green: %Lf\n", cg);
			printf("blue:  %Lf\n", cb);
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
	img->line_w = 1024;
	img->col_h = 512;
	*window_ptr = mlx_new_window(*mlx_ptr, img->line_w, img->col_h, "test");
	img->img = mlx_new_image(*mlx_ptr, img->line_w, img->col_h);
	img->addr = (int*)mlx_get_data_addr(img->img, &(img->bits_pixel),
			&(img->line_w), &(img->endian));
	img->line_w /= 4;
}

int	test_vecteur(int x, int y, t_img *img)
{
	int x_vec;
	int y_vec;
	int z_vec;

	x_vec = x - (img->line_w / 2);
	y_vec = y - (img->col_h / 2);
	z_vec = img->line_w / (2);// tan alpha);
	return (1);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*window_ptr;
	t_img	img;

	mlx_ptr = mlx_init();
	init_window_img(&img, &mlx_ptr, &window_ptr);

	colorful_background(img);
/*
	int sphere_x;
	int sphere_y;
	int sphere_z
	int sphere_diam;

	int camera_x;
	int camera_y;
	int camera_z;
	int camera_angle;
*/

	mlx_put_image_to_window(mlx_ptr, window_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (1);
}
