/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:13:44 by romain            #+#    #+#             */
/*   Updated: 2021/01/14 17:36:16 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

BOOL    is_intercept_sphere(t_vector *ray_o, t_vector *ray_dir, t_data *data)
{
        double		a;
        double		b;
        double		c;
        double		delta;
	t_sphere	*sphere;
        t_vector temp;

	sphere = &(data->sphere);
        temp = subtract_vectors(ray_o, &(sphere->origin));

//      printf("x: %Lf\n", ray_dir->x);
//      printf("y: %Lf\n", ray_dir->y);
//      printf("z: %Lf\n", ray_dir->z);

//      int     i = 0;
//      while (i < 1000000)     
//              i++;

        a = get_norme(ray_dir);
        b = get_scalar_product(&temp, ray_dir);
        c = get_norme(&temp) - sphere->radius * sphere->radius;
        delta = (b * b) - (a * c);
        if (delta < 0.0)
                return (FALSE);
	double root = (-b - sqrt(delta)) / a;
	if (root < 0 || root > 10000000.0)
	{
		root = (-b + sqrt(delta)) / a;
		if (root < 0 || root > 10000000.0)
		return (FALSE);
	}
	return (TRUE);
/*      
           long double t1;
           long double t2;

           t1 = (-b - sqrt(delta)) / (2.0 * a);
           t2 = (-b + sqrt(delta)) / (2.0 * a);
           if (t2 > 0.0)
           return (TRUE);
*/              return (FALSE);
}

static int		parse_sphere(t_obj *sphere, char* format)
{
	int	i;

	i = 2;
	if (!vector_microparser(&(sphere->data.sphere.origin), format, &i)
		|| !double_microparser(&(sphere->data.sphere.radius), format, &i)
		|| sphere->data.sphere.radius <= 0
		|| !color_microparser(&(sphere->color), format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (FALSE);
	sphere->f = is_intercept_sphere;

	printf("        %.1lf,%.1lf,%.1lf      ", sphere->data.sphere.origin.x, sphere->data.sphere.origin.y, sphere->data.sphere.origin.z);
	printf("%.1lf    ", sphere->data.sphere.radius);
	printf("%d     \n\n", sphere->color);         
	return (TRUE);
}

int		add_sphere(t_scene *scene, char *format)
{
	t_obj		*sphere;
	t_list		*temp_list;

	sphere = malloc(sizeof(t_obj));
	if (!sphere)
		return (FALSE);
	temp_list = list_new(sphere);
	if (!temp_list)
	{
		free(sphere);
		return (FALSE);
	}
	list_add_front(&(scene->object), temp_list);
	if (!parse_sphere(sphere, format))
		return (-1);
	return (TRUE);
}
