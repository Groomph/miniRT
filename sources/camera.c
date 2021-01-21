/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/21 05:08:56 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <math.h>

static void	set_lower_point(t_cam *cam)
{
	t_vector	z_bis;
	t_vector	x_bis;
	t_vector	y_bis;
	t_vector	temp;

	z_bis = sub_vectors(&(cam->o), &(cam->look_at));
	set_normalized(&z_bis);
	x_bis = get_vector_product(&(cam->vup), &z_bis);
	set_normalized(&x_bis);
	y_bis = get_vector_product(&z_bis, &x_bis);
	cam->horizontal = multiply_vector(&x_bis, cam->pov_w);
	cam->vertical = multiply_vector(&y_bis, cam->pov_h);
	temp = divide_vector(&(cam->horizontal), 2.0);
	cam->lower_corner = sub_vectors(&(cam->o), &temp);
	temp = divide_vector(&(cam->vertical), 2.0);
	cam->lower_corner = sub_vectors(&(cam->lower_corner), &temp);
	cam->lower_corner = sub_vectors(&(cam->lower_corner), &z_bis);
	printf("camera horizontal: %lf %lf %lf\n",
		cam->horizontal.x, cam->horizontal.y, cam->horizontal.z);
	printf("camera vertical: %lf %lf %lf\n",
		cam->vertical.x, cam->vertical.y, cam->vertical.z);
	printf("lower_corner: %lf %lf %lf\n",
		cam->lower_corner.x, cam->lower_corner.y, cam->lower_corner.z);
}

/*
**	cam->look_at = sub_vectors(&(cam->look_at), &(cam.o));
**	set_normalized(&(cam->look_at));
*/

void		param_camera(void *temp_cam, void *temp_img)
{
	t_cam	*cam;
	t_img	*img;
	double	ratio;

	cam = (t_cam*)temp_cam;
	img = (t_img*)temp_img;
	cam->fov_hori *= PI;
	cam->fov_hori /= 180;
	cam->fov_hori = tan(cam->fov_hori / 2);
	ratio = (double)img->line_w / (double)img->col_h;
	cam->pov_w = 2.0 * cam->fov_hori;
	cam->pov_h = cam->pov_w / ratio;
	set_lower_point(cam);
}

/*
**	cam->pov_h = 2.0 * cam->fov_hori;
**	cam->pov_w = cam->pov_h * ratio;
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
	cam->fov_hori = fov;
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
	{
		if (!vector_microparser(&(cam->look_at), format, &i))
			return (FALSE);
	}
	else
		cam->look_at = get_vector(0, 0.0, 0.0, -1.0);
	printf("        %.1lf,%.1lf,%.1lf      ", cam->o.x, cam->o.y, cam->o.z);
	printf("%.1lf,%.1lf,%.1lf      ", cam->vup.x, cam->vup.y, cam->vup.z);
	printf("%d         ", fov);
	printf("%.1lf,%.1lf,%.1lf \n\n",
				cam->look_at.x, cam->look_at.y, cam->look_at.z);
	return (TRUE);
}

int			add_camera(t_scene *scene, char *format)
{
	t_cam	*cam;
	t_list	*temp_list;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (-1);
	temp_list = list_new(cam);
	if (!temp_list)
	{
		free(cam);
		return (-1);
	}
	list_add_front(&(scene->cam_list), temp_list);
	if (!parse_camera(cam, format))
		return (FALSE);
	return (TRUE);
}
