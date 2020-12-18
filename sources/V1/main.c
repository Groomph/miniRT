#include "mlx.h"
#include <stdio.h>

typedef struct		s_img {
	void		*img;
	int		*addr;
	int		line_len_w;
	int		column_len_h;
	int		h;
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


int	main(void)
{
	void	*mlx_ptr;
	void	*window_ptr;

	mlx_ptr = mlx_init();
	window_ptr = mlx_new_window(mlx_ptr, 512, 512, "testwindow");

	t_img	img;
	int	bits_per_pixel;

	img.img = mlx_new_image(mlx_ptr, 512, 512);
	img.addr = (int*)mlx_get_data_addr(img.img, &bits_per_pixel,
						&img.line_len_w, &img.endian);
	img.line_len_w /= 4;
	int		i;
	int 		stop;
	long double	temp2;
	double 		cr;
	double		cg;
	double		cb;
	int		x;
	int		y;
	i = 0;
	stop = 512 * 512;
	while (i < stop)
	{
		x = i % img.line_len_w;
		y = i / img.line_len_w;
//		printf("x: %d\n", x);
//		printf("y: %d\n", y);
		cr = x / (double)(img.line_len_w - 1); 
		cg = y / (double)(img.line_len_w - 1);
		cb = ((x + (double)y) / (512 + 512)) - 1.0;
		if (cb < 0.0)
			cb *= -1;
		img.addr[(int)i] = build_color(0x0, cr * 255, cg * 255, cb * 255);
		i += 1.0;
	}
	mlx_put_image_to_window(mlx_ptr, window_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
write(1, "where", 5);	
	return (1);
}
