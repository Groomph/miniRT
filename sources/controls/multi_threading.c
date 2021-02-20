/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:28:08 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/20 03:43:51 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <pthread.h>
#include <stdio.h>

/*
static BOOL	malloc_tab(t_scene *scene)
{
//	int	i;

	//i = -1;
	while (++i < scene->thread_total)
	{
		scene->tab_thread[i] = (pthread_t*)(malloc(sizeof(pthread_t)));
		if (scene->tab_thread[i] == NULL)
		{
			while (--i >= 0)
				free(scene->tab_thread[i]);
			printf("Error while setting threads, render aborted");
			return (FALSE);
		}
	}
//	scene->tab_thread[scene->thread_total] = NULL;
	return (TRUE);
}*/

static void	launch_threads2(t_scene *scene, int y, int left)
{
	int		i;
	t_thread	*thread;

	i = -1;
	
	thread = malloc(sizeof(t_thread) * scene->thread_total);
	scene->attr_thread = malloc(sizeof(pthread_attr_t) * scene->thread_total);
//	if (!thread)
//		continue;
	while (++i < scene->thread_total)
	{
		pthread_attr_init(&scene->attr_thread[i]);
		thread[i].scene = scene;
		thread[i].y = i * y;
		thread[i].max_y = thread[i].y + y;
		if (left > 0)
		{
			thread[i].max_y++;
			left--;
		}
		thread[i].pixel = y * i * scene->img.line_w;
		thread[i].id = i;
		if (pthread_create(&scene->tab_thread[i], &scene->attr_thread[i], ray_caster, &thread[i]) != 0)
		{
			printf("Launch new thread has failed\n");
			continue;
		}
	//	scene->thread_on++;
	}
	i = -1;
	while (++i < scene->thread_total)
	{
		if (pthread_join(scene->tab_thread[i], NULL))
			printf("exit(1)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;\n");
	}
	i = -1;
	while (++i < scene->thread_total)
		pthread_attr_destroy(&scene->attr_thread[i]);
	free(scene->attr_thread);
	free(scene->tab_thread);
	free(thread);
	scene->attr_thread = NULL;
	scene->tab_thread = NULL;
	thread = NULL;
}

void		launch_threads(t_scene *scene)
{
//	int		i;
	int		y;
	int		left;

//	if (scene->thread_on != 0)
//	{
//		printf("render running\n");
//		return ;
//	}
//	if (scene->tab_thread)
//		free(scene->tab_thread);
	left = scene->img.col_h % scene->thread_total;
//	malloc_tab(scene);
	y = scene->img.col_h / scene->thread_total;
	scene->tab_thread = malloc(sizeof(pthread_t) * (scene->thread_total));
	if (scene->tab_thread)
		launch_threads2(scene, y, left);
//		i = -1;
//		while (scene->tab_thread[++i] != NULL)
//			free(scene->tab_thread[i]);
}

/*
**		printf("pixel: %d\n", thread->pixel);
**		printf("y: %d\n", thread->y);
**		printf("max_y: %d\n", thread->max_y);
**		printf("i: %d\n", i);
*/
