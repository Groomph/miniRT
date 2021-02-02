/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/02 13:19:09 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
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

	focale = sub_vectors(&(cam->o), &(cam->look_at));
	set_normalized(&focale);
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

static void		param_camera(t_cam *cam, double w, double h)
{
	double		ratio;
	t_vector	focale;
	t_vector	cross;

	cam->fov_hori *= PI;
	cam->fov_hori /= 180.0;
	cam->fov_hori = tan(cam->fov_hori / 2.0);
	ratio = w / h;
	cam->pov_w = 2.0 * cam->fov_hori;
	cam->pov_h = cam->pov_w / ratio;
	focale = sub_vectors(&(cam->o), &(cam->look_at));
	set_normalized(&focale);
	cross = get_vector_product(&(cam->vup), &focale);
	if (get_norme(&cross) == 0)
		cross = get_z_rotation(&focale, 90.0);
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

BOOL	set_resolution(t_img *img, char *format)
{
	int	i;

	if (img->set)
		return (FALSE);
	i = 1;
	if (!int_microparser(&(img->line_w), format, &i))
		return (FALSE);
	if (!int_microparser(&(img->col_h), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	img->set = TRUE;
	return (TRUE);
}

static void	parsing_rt_file(t_scene *scene, t_img *img, int fd)
{
	int		check;
	char	*line;
	int		line_nb;
	int		previous;

	check = 1;
	line = NULL;
	line_nb = 0;
	previous = 20;
	while (check > 0)
	{
		check = get_next_line(fd, &line);
		printf("%d      %s\n", check, line);
		if (check == -1)
		{
			if (line)
				free(line);
			close(fd);
			stop_program(scene, 14, line_nb);
		}
		if (line[0] != '\0')
			previous = add_object(scene, line, line_nb++, previous);
		free(line);
		line = NULL;
	}
}

void		check_prog_args(t_scene *scene, t_img *img, int ac, char **av)
{
	int		fd;
	t_cam	*temp_cam;

	fd = -1;
	if (ac > 3 || ac == 1)
		stop_program(scene, 13, -1);
	if (ac == 3 && !str_n_comp(av[2], "-save", 6))
		scene->saveit = 1;
	else if (ac == 3)
		stop_program(scene, 12, -1);
	if (str_nstr_comp(av[1], ".rt\0", 4))
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
		stop_program(scene, 11, -1);
	parsing_rt_file(scene, img, fd);
	close(fd);
	if (!(img->set) || !(scene->cam_list) || !(scene->ambient_is_set))
		stop_program(scene, 7, -1);
	temp_cam = scene->cam_list;
	while (temp_cam)
	{
		param_camera(temp_cam, img->line_w, img->col_h);
		temp_cam = temp_cam->next;
	}
	scene->cam = scene->cam_list;
}
