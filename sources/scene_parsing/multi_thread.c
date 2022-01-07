/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:55:41 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 15:05:52 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

BOOL	set_multi_threading(t_scene *scene, char *format)
{
	int	i;

	i = 2;
	if (!int_microparser(&(scene->thread_total), format, &i)
		|| scene->thread_total < 1)
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	printf("        %d\n\n", scene->thread_total);
	return (TRUE);
}
