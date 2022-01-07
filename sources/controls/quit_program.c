/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:16:18 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 16:47:06 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>

static void	error_printer(int errornb, int line)
{
	char	*error_tab[15];

	error_tab[1] = "Not supposed to happen";
	error_tab[2] = "Not supposed to happen";
	error_tab[3] = "Error\nn°3: Double bonus parameters, line ";
	error_tab[4] = "Error\nn°4: Wrong object identifier, line ";
	error_tab[5] = "Error\nn°5: Malloc error, line ";
	error_tab[6] = "Error\nn°6: Wrong line format, line ";
	error_tab[7] = "Error\nn°7: Missing essential object(s)";
	error_tab[8] = "Not supposed to happen";
	error_tab[9] = "Not supposed to happen";
	error_tab[10] = "Not supposed to happen";
	error_tab[11] = "Error\nn°11: Invalid path or file name";
	error_tab[12] = "Error\nn°12: Unknown second argument";
	error_tab[13] = "Error\nn°13: Wrong number of arguments";
	error_tab[14] = "Error\nn°14: Error while reading file";
	if (line >= 0)
		printf("%s%d\n", error_tab[errornb], line);
	else
		printf("%s\n", error_tab[errornb]);
}

void	error_parsing(t_scene *scene, int fd, int errornb, int line)
{
	char	*temp;
	int		check;

	check = 1;
	while (fd > -1 && check > 0)
	{
		check = get_next_line(fd, &temp);
		free(temp);
	}
	if (fd > -1)
		close(fd);
	error_printer(errornb, line);
	stop_program(scene);
}

static void	clear_all(t_cam *cam, t_light *light, t_obj *obj)
{
	if (cam)
	{
		clear_all(cam->next, NULL, NULL);
		free(cam);
	}
	if (light)
	{
		clear_all(NULL, light->next, NULL);
		free(light);
	}
	if (obj)
	{
		clear_all(NULL, NULL, obj->next);
		free(obj);
	}
}

int	stop_program(t_scene *scene)
{
	int	i;

	i = 0;
	clear_all(scene->cam_list, scene->light, scene->object);
	if (scene->window)
		mlx_destroy_window(scene->mlx, scene->window);
	if (scene->img.img)
		mlx_destroy_image(scene->mlx, scene->img.img);
	while (i < 6)
	{
		if (scene->skybox[i].img)
			mlx_destroy_image(scene->mlx, scene->skybox[i].img);
		i++;
	}
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	exit(0);
	return (1);
}

/*
**	//	mlx_do_key_autorepeaton(scene->mlx);
*/
