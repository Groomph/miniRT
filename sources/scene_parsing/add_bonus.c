/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 01:01:10 by romain            #+#    #+#             */
/*   Updated: 2022/01/07 15:48:56 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

static void	set_bonus_compound(t_obj *obj, int i)
{
	t_obj	*temp;

	temp = obj->next;
	while (i-- > 0)
	{
		temp->specular = obj->specular;
		temp->check_board = obj->check_board;
		temp->rainbow = obj->rainbow;
		temp->perlin = obj->perlin;
		temp->marbre = obj->marbre;
		temp->liana = obj->liana;
		temp->water = obj->water;
		temp->wave = obj->wave;
		temp = temp->next;
	}
}

static BOOL	set_object_bonus3(t_obj *obj, char *format, int *i)
{
	if (str_n_comp(&(format[*i]), "PERLIN", 6) == 0)
	{
		(*i) += 2;
		obj->perlin = TRUE;
	}
	else if (str_n_comp(&(format[*i]), "MARBRE", 6) == 0)
	{
		(*i) += 2;
		obj->marbre = TRUE;
	}
	else if (str_n_comp(&(format[*i]), "LIANA", 5) == 0 && ++(*i))
		obj->liana = TRUE;
	else if (str_n_comp(&(format[*i]), "WATER", 5) == 0 && ++(*i))
		obj->water = TRUE;
	else if (str_n_comp(&(format[*i]), "WAVE", 4) == 0)
		obj->wave = TRUE;
	else if (str_n_comp(&(format[*i]), "CAPS", 4) == 0)
		obj->caps = TRUE;
	else
		return (FALSE);
	*i += 4;
	return (TRUE);
}

static BOOL	set_object_bonus2(t_obj *obj, char *format, int *i)
{
	while (format[*i] == ' ')
		(*i)++;
	if (str_n_comp(&(format[*i]), "SPECULAR", 8) == 0)
	{
		(*i) += 8;
		obj->specular = TRUE;
	}
	else if (str_n_comp(&(format[*i]), "CHECK_BOARD", 11) == 0)
	{
		(*i) += 11;
		obj->check_board = TRUE;
	}
	else if (str_n_comp(&(format[*i]), "RAINBOW", 7) == 0)
	{
		(*i) += 7;
		obj->rainbow = TRUE;
	}
	else
		return (set_object_bonus3(obj, format, i));
	return (TRUE);
}

static BOOL	set_object_bonus(t_scene *scene, t_obj *obj, char *format,
									int i)
{
	if (!set_object_bonus2(obj, format, &i))
		return (FALSE);
	while (format[i] == ' ')
		i++;
	if (format[i] != '\0')
		return (set_object_bonus(scene, obj, format, i));
	if (obj->caps == TRUE)
		if (obj->type != CYLINDER || !add_disk(scene, obj, 0))
			return (FALSE);
	if ((obj->type == CYLINDER && obj->caps) || obj->type == CUBE
		|| obj->type == PYRAMIDE)
		set_bonus_compound(obj, obj->type);
	return (TRUE);
}

int	add_bonus(t_scene *scene, char *format, int previous)
{
	int	check;

	if (previous == 20)
		return (-3);
	else if (previous == 3)
		check = set_camera_bonus(scene->cam_list, format, 5);
	else if (previous == 4)
		check = set_light_bonus(scene->light, format, 5);
	else if (previous >= 5)
		check = set_object_bonus(scene, scene->object, format, 5);
	else
		check = -2;
	if (check < TRUE)
		return (FALSE);
	return (20);
}
