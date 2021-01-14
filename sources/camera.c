/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:21:17 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/14 17:35:12 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <math.h>

void		param_camera(void *temp_cam, void *temp_img)
{
	t_cam		*cam;
	t_img		*img;
	double		ratio;
	t_vector	w;
	t_vector	u;
	t_vector	v;
	t_vector	temp;
	
	cam = (t_cam*)temp_cam;
	img = (t_img*)temp_img;
	cam->fov_hori *=  PI;
	cam->fov_hori /=  180;
	cam->fov_hori = tan(cam->fov_hori / 2);

	ratio = (double)img->line_w / (double)img->col_h;
	cam->pov_w = 2.0 * cam->fov_hori;
	cam->pov_h = cam->pov_w / ratio;

/*	cam->pov_h = 2.0 * cam->fov_hori;
	cam->pov_w = cam->pov_h * ratio;
*/
	w = subtract_vectors(&(cam->origin), &(cam->look_at));
	get_normalized(&w);
	u = get_vector_product(&(cam->vup), &w);
	get_normalized(&u);
	v = get_vector_product(&w, &u);
	cam->horizontal = multiply_vector(&u, cam->pov_w);
	cam->vertical = multiply_vector(&v, cam->pov_h);
	temp = divide_vector(&(cam->horizontal), 2.0);
	cam->lower_corner = subtract_vectors(&(cam->origin), &temp);
	temp = divide_vector(&(cam->vertical), 2.0);
	cam->lower_corner = subtract_vectors(&(cam->lower_corner), &temp);
	cam->lower_corner = subtract_vectors(&(cam->lower_corner), &w);
}

static int		parse_camera(t_cam *cam, char* format)
{
	int	i;
	int	fov;

	i = 1;
	if (!vector_microparser(&(cam->origin), format, &i)
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
		set_vector(&(cam->look_at), 0.0, 0.0, -1.0);
	printf("        %.1lf,%.1lf,%.1lf      ", cam->origin.x, cam->origin.y, cam->origin.z);
	printf("%.1lf,%.1lf,%.1lf      ", cam->vup.x, cam->vup.y, cam->vup.z);
	printf("%d         ", fov); 	
 	printf("%.1lf,%.1lf,%.1lf \n\n", cam->look_at.x, cam->look_at.y, cam->look_at.z);
	return (TRUE);
}

int		add_camera(t_scene *scene, char *format)
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
	list_add_front(&(scene->cam), temp_list);
	if (!parse_camera(cam, format))
		return (FALSE);
	return (TRUE);
}
