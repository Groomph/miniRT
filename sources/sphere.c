/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:13:44 by romain            #+#    #+#             */
/*   Updated: 2020/12/21 18:26:30 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

BOOL    is_intercept_sphere(t_vector *ray_o, t_vector *ray_dir, t_sphere *sphere)
{
        double     a;
        double     b;
        double     c;
        double     delta;

        t_vector temp;
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
        if (delta >= 0.0)
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

