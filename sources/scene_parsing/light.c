/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:24:16 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/27 14:06:13 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

static int	parse_light(t_light *light, char *format)
{
	int	i;

	i = 1;
	if (!vector_microparser(&(light->o), format, &i)
		|| !double_microparser(&(light->intensity), format, &i)
		|| light->intensity < 0
		|| light->intensity > 1
		|| !color_microparser(&(light->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	printf("        %.1lf,%.1lf,%.1lf      ", light->o.x, light->o.y,
								light->o.z);
	printf("%.2lf    ", light->intensity);
	printf("         %.1lf,%.1lf,%.1lf,%.1lf\n\n", light->color.other,
			light->color.x, light->color.y, light->color.z);
	return (TRUE);
}

int			add_light(t_scene *scene, char *format)
{
	t_light		*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (FALSE);
	light->next = scene->light;
	scene->light = light;
	if (!parse_light(light, format))
		return (-1);
	return (TRUE);
}
