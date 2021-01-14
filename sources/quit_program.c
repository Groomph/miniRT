/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:49:17 by romain            #+#    #+#             */
/*   Updated: 2021/01/13 18:25:37 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	error_printer(int errornb, int line)
{
	char	*error_tab[14];

	error_tab[0] = "";
	error_tab[3] = "Error while reading file\n";
	error_tab[4] = "Wrong object identifier, line ";
	error_tab[5] = "Malloc error, line ";
	error_tab[6] = "Wrong line format, line ";
	error_tab[7] = "Missing essential object(s)";
	error_tab[11] = "Invalid path or file name\n";
	error_tab[12] = "Unknown second argument\n";
	error_tab[13] = "Wrong number of arguments\n";
	if (line >= 0)
		printf("%s%d\n", error_tab[errornb], line);
	else
		printf("%s", error_tab[errornb]);
}

void		stop_program(t_scene *scene, int errornb, int line)
{
	error_printer(errornb, line);
	list_clear(&(scene->cam), 0);
	list_clear(&(scene->object), 0);
	exit(0);
}
