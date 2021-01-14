/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/13 18:40:28 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int	set_resolution(t_scene *scene, char *format)
{
	int	i;

	if (scene->img.set == FALSE)
	{
		i = 1;
		if (!int_microparser(&(scene->img.line_w), format, &i)
		|| !int_microparser(&(scene->img.col_h), format, &i))
			return (FALSE);
		while (format[i] == ' ')
			i++;
		if (format[i] != '\0')
			return(FALSE);
		scene->img.set = 1;
	}
	else
		return(FALSE);
	return (TRUE);
}

static void	add_object(t_scene *scene, char *line, int count_line)
{
	int check;

	if (str_n_comp(line, "c ", 2) == 0)
		check = add_camera(scene, line);
	else if (str_n_comp(line, "R ", 2) == 0)
		check = set_resolution(scene, line);
	else if (str_n_comp(line, "sp ", 3) == 0)
		check = add_sphere(scene, line);
	else
		check = -2;
	if (check != TRUE)
		stop_program(scene, check + 6, count_line);
}

static void	parsing_rt_file(t_scene *scene, int fd)
{
	int	check;
	char	*temp_line;
	int	count_line;

	check = 1;
	temp_line = NULL;
	count_line = 0;
	while (check > 0)
	{
		check = get_next_line(fd, &temp_line);
		printf("%d        ", check);
		printf("%s\n", temp_line);
		if (check == -1)
		{
			if (temp_line)
				free(temp_line);
			close(fd);
			stop_program(scene, 3, count_line);
		}
		if (temp_line[0] != '\0')
			add_object(scene, temp_line, count_line);
		count_line++;
		free(temp_line);
		temp_line = NULL;
	}
}

void		check_prog_args(t_scene *scene, int ac, char **av)
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
		parsing_rt_file(scene, fd);
		close(fd);
	}
	if (!scene->img.set || !scene->cam/* || !scene->ambiant_light*/)
			stop_program(scene, 7, -1);
	list_iter(scene->cam, param_camera, &(scene->img));
	scene->active_cam = scene->cam->object;
}
