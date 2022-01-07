/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 15:33:37 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

BOOL	set_camera_bonus3(t_cam *cam, char *format, int *i)
{
	if (str_n_comp(&(format[*i]), "LOOK_AT=", 8) == 0)
	{
		*i += 8;
		if (!vector_microparser(&(cam->look_at), format, i))
			return (FALSE);
		cam->look_at = sub_vectors(&(cam->look_at), &(cam->o));
		if (!set_normalized(&(cam->look_at)))
			return (FALSE);
	}
	else if (str_n_comp(&(format[*i]), "GAMMA", 5) == 0)
	{
		*i += 5;
		cam->gamma = TRUE;
	}
	else
		return (FALSE);
	return (TRUE);
}

BOOL	set_camera_bonus2(t_cam *cam, char *format, int *i)
{
	if (str_n_comp(&(format[*i]), "ANTI_ALIASING=", 14) == 0)
	{
		*i += 14;
		if (!int_microparser(&(cam->anti_aliasing), format, i)
			|| cam->anti_aliasing < 1 || cam->anti_aliasing > 100)
			return (FALSE);
	}
	else if (str_n_comp(&(format[*i]), "RECURSIVITY=", 12) == 0)
	{
		*i += 12;
		if (!int_microparser(&(cam->recursivity), format, i)
			|| cam->recursivity < 0 || cam->recursivity > 100)
			return (FALSE);
	}
	else
		return (set_camera_bonus3(cam, format, i));
	return (TRUE);
}

BOOL	set_camera_bonus(t_cam *cam, char *format, int i)
{
	int	check;

	check = 1;
	while (format[i] == ' ')
		i++;
	if (!set_camera_bonus2(cam, format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (set_camera_bonus(cam, format, i));
	if (cam->o.x == cam->look_at.x && cam->o.y == cam->look_at.y
		&& cam->o.z == cam->look_at.z)
		return (FALSE);
	return (TRUE);
}

static int	parse_camera(t_cam *cam, char *format)
{
	int	i;
	int	fov;

	i = 1;
	if (!vector_microparser(&(cam->o), format, &i)
		|| !vector_microparser(&(cam->vup), format, &i)
		|| !int_microparser(&fov, format, &i) || fov < 1 || fov > 180)
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	cam->look_at = get_vector(0.0, 0.0, 0.0, -1.0);
	cam->fov_hori = (double)fov;
	cam->fov_hori *= PI;
	cam->fov_hori /= 180.0;
	cam->fov_hori = tan(cam->fov_hori / 2.0);
	cam->anti_aliasing = 1;
	cam->recursivity = 0;
	cam->gamma = FALSE;
	return (TRUE);
}

int	add_camera(t_scene *scene, char *format)
{
	t_cam	*cam;
	int		norme;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (-1);
	cam->next = scene->cam_list;
	scene->cam_list = cam;
	if (!parse_camera(cam, format))
		return (FALSE);
	norme = set_normalized(&(cam->vup));
	if (norme == 0)
		return (FALSE);
	printf("        %.1lf,%.1lf,%.1lf      ", cam->o.x, cam->o.y, cam->o.z);
	printf("%.1lf,%.1lf,%.1lf      ", cam->vup.x, cam->vup.y, cam->vup.z);
	printf("%.1lf         ", cam->fov_hori);
	printf("%.1lf,%.1lf,%.1lf \n\n",
		cam->look_at.x, cam->look_at.y, cam->look_at.z);
	return (TRUE + 2);
}
