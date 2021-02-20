/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:27:52 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/18 19:05:54 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdio.h>

void	set_coef(t_control *control, int key)
{
	if (key == PLUS)
		control->coef++;
	if (key == MINUS)
		control->coef--;
	if (control->coef < 1)
		control->coef = 1;
	printf("Coef set at %d\n", control->coef);
}

void	set_threads_number(t_scene *scene, int key)
{
	if (key == R && scene->thread_total > 1)
		scene->thread_total--;
	else if (key == T)
		scene->thread_total++;
	printf("Threads number set at %d\n", scene->thread_total);
}
