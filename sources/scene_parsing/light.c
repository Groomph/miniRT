/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:24:16 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 15:10:12 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

BOOL	set_ambient_light(t_scene *scene, char *format)
{
	int	i;

	if (scene->ambient_is_set)
		return (FALSE);
	i = 1;
	if (!double_microparser(&(scene->ambient.intensity), format, &i)
		|| scene->ambient.intensity <= 0
		|| scene->ambient.intensity >= 1
		|| !color_microparser(&(scene->ambient.color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	scene->ambient_is_set = TRUE;
	printf("      %.2lf", scene->ambient.intensity);
	printf("      %.1lf,%.1lf,%.1lf,%.1lf\n\n", scene->ambient.color.other,
		scene->ambient.color.x, scene->ambient.color.y,
		scene->ambient.color.z);
	return (TRUE + 1);
}

BOOL	set_light_bonus(t_light *light, char *format, int i)
{
	double	norme;

	while (format[i] == ' ')
		i++;
	if (str_n_comp(&(format[i]), "PARALLEL", 8) == 0)
	{
		i += 8;
		norme = set_normalized((&light->o));
		if (norme == 0)
			return (FALSE);
		light->parallel = TRUE;
	}
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

int	add_light(t_scene *scene, char *format)
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
