/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/29 11:21:06 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

static void	set_lower_point(t_cam *cam)
{
	t_vector	focale;
	t_vector	temp;

	focale = sub_vectors(&(cam->o), &(cam->look_at));
	set_normalized(&focale);
	temp = divide_vector(&(cam->horizontal), 2.0);
	cam->lower_corner = sub_vectors(&(cam->o), &temp);
	temp = divide_vector(&(cam->vertical), 2.0);
	cam->lower_corner = sub_vectors(&(cam->lower_corner), &temp);
	cam->lower_corner = sub_vectors(&(cam->lower_corner), &focale);
	printf("camera horizontal: %lf %lf %lf\n",
		cam->horizontal.x, cam->horizontal.y, cam->horizontal.z);
	printf("camera vertical: %lf %lf %lf\n",
		cam->vertical.x, cam->vertical.y, cam->vertical.z);
	printf("lower_corner: %lf %lf %lf\n",
		cam->lower_corner.x, cam->lower_corner.y, cam->lower_corner.z);
	printf("focale: %lf %lf %lf\n", focale.x, focale.y, focale.z);
}

/*
**	cam->look_at = sub_vectors(&(cam->look_at), &(cam.o));
**	set_normalized(&(cam->look_at));
*/

void		param_camera(t_cam *cam, double w, double h)
{
	double		ratio;
	t_vector	focale;
	t_vector	cross;

	cam->fov_hori *= PI;
	cam->fov_hori /= 180.0;
	cam->fov_hori = tan(cam->fov_hori / 2.0);
	ratio = w / h;
	cam->pov_w = 2.0 * cam->fov_hori;
	cam->pov_h = cam->pov_w / ratio;
	focale = sub_vectors(&(cam->o), &(cam->look_at));
	set_normalized(&focale);
	cross = get_vector_product(&(cam->vup), &focale);
	if (get_norme(&cross) == 0)
		cross = get_z_rotation(&focale, 90.0);
	set_normalized(&cross);
	cam->horizontal = multiply_vector(&cross, cam->pov_w);
	cross = get_vector_product(&focale, &cross);
	set_normalized(&cross);
	cam->vertical = multiply_vector(&cross, cam->pov_h);
	set_lower_point(cam);
}

/*
**	cam->pov_h = 2.0 * cam->fov_hori;
**	cam->pov_w = cam->pov_h * ratio;
**	set_normalized(&focale);
**	set_normalized(&(cam->vup));
**	printf("cross2\n");
**	set_normalized(&cross);
*/

static int	parse_camera(t_cam *cam, char *format)
{
	int	i;
	int	fov;

	i = 1;
	if (!vector_microparser(&(cam->o), format, &i)
		|| !vector_microparser(&(cam->vup), format, &i)
		|| !int_microparser(&fov, format, &i) || fov < 1 || fov > 180)
		return (FALSE);
	cam->fov_hori = (double)fov;
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
	{
		if (!vector_microparser(&(cam->look_at), format, &i))
			return (FALSE);
		while (format[i] == ' ')
			i++;
		if (format[i] != '\0')
			return (FALSE);
	}
	else
		cam->look_at = get_vector(0.0, 0.0, 0.0, -1.0);
	return (TRUE);
}

int			add_camera(t_scene *scene, char *format)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (-1);
	cam->next = scene->cam_list;
	scene->cam_list = cam;
	if (!parse_camera(cam, format))
		return (FALSE);
	if (get_norme(&(cam->vup)) == 0.0 || (cam->o.x == cam->vup.x
			&& cam->o.y == cam->vup.y && cam->o.z == cam->vup.z))
		return (FALSE);
	printf("        %.1lf,%.1lf,%.1lf      ", cam->o.x, cam->o.y, cam->o.z);
	printf("%.1lf,%.1lf,%.1lf      ", cam->vup.x, cam->vup.y, cam->vup.z);
	printf("%.1lf         ", cam->fov_hori);
	printf("%.1lf,%.1lf,%.1lf \n\n",
				cam->look_at.x, cam->look_at.y, cam->look_at.z);
	return (TRUE);
}
