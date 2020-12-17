#include "mlx.h"
#include <stdio.h>

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	printf("%c\n", -555.5);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 512, 512, "testwindow");
	mlx_loop(mlx_ptr);
	return (1);
}
