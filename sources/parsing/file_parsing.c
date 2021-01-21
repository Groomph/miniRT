/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/21 00:18:03 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static BOOL	set_resolution(t_img *img, char *format)
{
	int	i;

	if (img->set == TRUE)
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

	if (str_n_comp(line, "c ", 2) == 0)
		check = add_camera(scene, line);
	else if (str_n_comp(line, "R ", 2) == 0)
		check = set_resolution(img, line);
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
	int	fd;

	fd = -1;
	if (ac > 3 || ac == 1)
		stop_program(scene, 13, -1);
	else
	{
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
	}
	if (!img->set || !scene->cam_list)
		stop_program(scene, 7, -1);
	list_iter(scene->cam_list, param_camera, img);
	scene->cam = scene->cam_list->object;
}

/*
**if (!img->set || !scene->cam_list || !scene->ambiant_light)
*/
