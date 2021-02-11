/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:24:16 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/02 17:09:07 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

BOOL		set_ambient_light(t_scene *scene, char *format)
{
	int	i;

	if (scene->ambient_is_set)
		return (FALSE);
	i = 1;
	if (!double_microparser(&(scene->ambient_intensity), format, &i)
			|| scene->ambient_intensity <= 0
			|| scene->ambient_intensity >= 1
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
	return (TRUE + 1);
}

BOOL		set_light_bonus(t_light *light, char *format, int i)
{
	while (format[i] == ' ')
		i++;
	if (str_n_comp(&(format[i]), "PARALLEL", 8) == 0 && (i += 8))
		light->parallel = TRUE;
	else
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (set_light_bonus(light, format, i));
	return (TRUE);
}

static int	parse_light(t_light *light, char *format)
{
	int	i;

	i = 1;
	if (!vector_microparser(&(light->o), format, &i)
			|| !double_microparser(&(light->intensity), format, &i)
			|| light->intensity <= 0
			|| light->intensity >= 1
			|| !color_microparser(&(light->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	light->parallel = FALSE;
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
		return (-1);
	light->next = scene->light;
	scene->light = light;
	if (!parse_light(light, format))
		return (FALSE);
	return (TRUE + 3);
}
