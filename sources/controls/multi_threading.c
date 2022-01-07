/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:28:08 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 14:59:56 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>

static void	join_thread(int i, int max, pthread_t *tab_thread)
{
	while (++i < max)
	{
		if (pthread_join(tab_thread[i], NULL))
			printf("Error thread_join\n");
	}
}

static BOOL	threads(t_scene *scene, int y, int left, pthread_t *tab_thread)
{
	int			i;
	t_thread	*thread;

	thread = malloc(sizeof(t_thread) * scene->thread_total);
	if (!thread)
		return (FALSE);
	i = -1;
	while (++i < scene->thread_total)
	{
		thread[i].scene = scene;
		thread[i].y = i * y;
		thread[i].max_y = thread[i].y + y;
		if (left-- > 0)
			thread[i].max_y++;
		if (thread[i].max_y >= scene->img.col_h)
			thread[i].max_y = scene->img.col_h;
		thread[i].pixel = y * i * scene->img.line_w;
		thread[i].id = i;
		if (pthread_create(&tab_thread[i], NULL, ray_caster,
				&thread[i]) != 0)
			printf("Launch new thread has failed\n");
	}
	join_thread(-1, scene->thread_total, tab_thread);
	free(thread);
	return (TRUE);
}

static void	controls_message(void)
{
	printf("Rendering done\n");
	printf("ESCAPE = quit miniRT\nENTER = launch render\n");
	printf("- = decrease move speed and rotation\n");
	printf("+ = increase move speed and rotation\n");
	printf("R = decrease number of render thread\n");
	printf("T = increase number of render thread\n");
	printf("A, E, ARROWS = rotate the camera or the selected object\n");
	printf("Z, Q, S, D, CTRL, SPACE = ");
	printf("move the camera or the selected object\n");
	printf("LEFT CLICK = move the camera\n");
	printf("RIGHT CLICK = select the object\n");
	printf("TAB = deselect object if selected\n");
}

void	launch_threads(t_scene *scene)
{
	int			y;
	int			left;
	pthread_t	*tab_thread;

	tab_thread = malloc(sizeof(pthread_t) * (scene->thread_total));
	if (tab_thread)
	{
		left = scene->img.col_h % scene->thread_total;
		y = scene->img.col_h / scene->thread_total;
		threads(scene, y, left, tab_thread);
		free(tab_thread);
	}
	controls_message();
}

/*
**	mlx_put_image_to_window(scene->mlx, scene->window,
**					scene->img.img, 0, 0);
*/

/*
**		printf("pixel: %d\n", thread->pixel);
**		printf("y: %d\n", thread->y);
**		printf("max_y: %d\n", thread->max_y);
**		printf("i: %d\n", i);
*/
