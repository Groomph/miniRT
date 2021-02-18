/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/18 00:54:44 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void	set_lower_point(t_cam *cam)
{
	t_vector	focale;
	t_vector	temp;

	focale = multiply_vector(&(cam->look_at), -1);
	temp = divide_vector(&(cam->horizontal), 2.0);
	cam->lower_corner = sub_vectors(&(cam->o), &temp);
	temp = divide_vector(&(cam->vertical), 2.0);
	cam->lower_corner = sub_vectors(&(cam->lower_corner), &temp);
	cam->lower_corner = sub_vectors(&(cam->lower_corner), &focale);
	printf("camera horizontal: %lf %lf %lf\n",
		cam->horizontal.x, cam->horizontal.y, cam->horizontal.z);
	printf("camera vertical: %lf %lf %lf\n",
		cam->vertical.x, cam->vertical.y, cam->vertical.z);
	printf("lower_corner: %lf %lf %lf\n",
		cam->lower_corner.x, cam->lower_corner.y, cam->lower_corner.z);
	printf("focale: %lf %lf %lf\n", focale.x, focale.y, focale.z);
}

/*
**	cam->look_at = sub_vectors(&(cam->look_at), &(cam.o));
**	set_normalized(&(cam->look_at));
*/

void		param_camera(t_cam *cam, double w, double h)
{
	double		ratio;
	t_vector	focale;
	t_vector	cross;

	ratio = w / h;
	cam->pov_w = 2.0 * cam->fov_hori;
	cam->pov_h = cam->pov_w / ratio;
	focale = multiply_vector(&(cam->look_at), -1);
	cross = get_vector_product(&(cam->vup), &focale);
	if (get_norme(&cross) == 0)
		cross = get_z_rotation(&focale, 90.0, FALSE);
	set_normalized(&cross);
	cam->horizontal = multiply_vector(&cross, cam->pov_w);
	cross = get_vector_product(&focale, &cross);
	set_normalized(&cross);
	cam->vertical = multiply_vector(&cross, cam->pov_h);
	set_lower_point(cam);
}

/*
**	cam->pov_h = 2.0 * cam->fov_hori;
**	cam->pov_w = cam->pov_h * ratio;
**	set_normalized(&focale);
**	set_normalized(&(cam->vup));
**	printf("cross2\n");
**	set_normalized(&cross);
*/

BOOL	set_resolution(t_scene *scene, t_img *img, char *format)
{
	int		i;
	int		max_x;
	int		max_y;
	long int	max;

	if (img->set)
		return (FALSE);
	i = 1;
	mlx_get_screen_size(scene->mlx, &max_x, &max_y);
	if (!int_microparser(&(img->line_w), format, &i)
		|| !int_microparser(&(img->col_h), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	max = img->line_w * img->col_h;
	if (format[i] != '\0' || img->line_w <= 0 || img->col_h <= 0
							|| max > 1000000000)
		return (FALSE);
	if (!scene->saveit && img->line_w > max_x)
		img->line_w = max_x;
	if (!scene->saveit && img->col_h > max_y)
		img->col_h = max_y;
	img->set = TRUE;
	img->col_h += (img->col_h % 4 > 0) ? 4 - (img->col_h % 4) : 0;
	return (TRUE);
}

static void	parsing_rt_file(t_scene *scene, t_img *img, int fd)
{
	int		check;
	char	*line;
	int		line_nb;
	int		previous;

	check = 1;
	line_nb = 0;
	previous = 20;
	while (check > 0 && ++line_nb)
	{
		check = get_next_line(fd, &line);
		printf("%d      %s\n", check, line);
		if (check == -1)
			error_parsing(scene, fd, 14, line_nb);
		else if (line[0] != '\0')
			previous = add_object(scene, line, previous);
		free(line);
		if (previous < TRUE)
			error_parsing(scene, fd, previous + 6, line_nb);
	}
}

void		check_prog_args(t_scene *scene, t_img *img, int ac, char **av)
{
	int		fd;
	t_cam	*temp_cam;

	fd = -1;
	if (ac > 3 || ac == 1)
		error_parsing(scene, fd, 13, -1);
	if (ac == 3 && !str_n_comp(av[2], "-save", 6))
		scene->saveit = 1;
	else if (ac == 3)
		error_parsing(scene, fd, 12, -1);
	if (str_nstr_comp(av[1], ".rt\0", 4))
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_parsing(scene, -1, 11, -1);
	parsing_rt_file(scene, img, fd);
	close(fd);
	if (!(img->set) || !(scene->cam_list) || !(scene->ambient_is_set))
		error_parsing(scene, -1, 7, -1);
	temp_cam = scene->cam_list;
	while (temp_cam)
	{
		param_camera(temp_cam, img->line_w, img->col_h);
		temp_cam = temp_cam->next;
	}
	scene->cam = scene->cam_list;
}
