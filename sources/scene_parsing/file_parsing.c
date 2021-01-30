/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/29 11:17:28 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static BOOL	set_ambient_light(t_scene *scene, char *format)
{
	int	i;

	if (scene->ambient_is_set)
		return (FALSE);
	i = 1;
	if (!double_microparser(&(scene->ambient_intensity), format, &i)
		|| scene->ambient_intensity < 0
		|| scene->ambient_intensity > 1
		|| !color_microparser(&(scene->ambient_light), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	printf("        %.1lf,%.1lf,%.1lf      ", scene->ambient_light.x,
			scene->ambient_light.y,
			scene->ambient_light.z);
	scene->ambient_is_set = TRUE;
	printf("%.2lf\n\n", scene->ambient_intensity);
	return (TRUE);
}

static BOOL	set_resolution(t_img *img, char *format)
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

static void	add_object(t_scene *scene, t_img *img, char *line, int line_nb)
{
	int check;

	if (str_n_comp(line, "R ", 2) == 0)
		check = set_resolution(img, line);
	else if (str_n_comp(line, "A ", 2) == 0)
		check = set_ambient_light(scene, line);
	else if (str_n_comp(line, "c ", 2) == 0)
		check = add_camera(scene, line);
	else if (str_n_comp(line, "l ", 2) == 0)
		check = add_light(scene, line);
	else if (str_n_comp(line, "sp ", 3) == 0)
		check = add_sphere(scene, line);
	else
		check = -2;
	if (check != TRUE)
		stop_program(scene, check + 6, line_nb);
}

static void	parsing_rt_file(t_scene *scene, t_img *img, int fd)
{
	int		check;
	char	*line;
	int		line_nb;

	check = 1;
	line = NULL;
	line_nb = 0;
	while (check > 0)
	{
		check = get_next_line(fd, &line);
		printf("%d        ", check);
		printf("%s\n", line);
		if (check == -1)
		{
			if (line)
				free(line);
			close(fd);
			stop_program(scene, 3, line_nb);
		}
		if (line[0] != '\0')
			add_object(scene, img, line, line_nb);
		line_nb++;
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
