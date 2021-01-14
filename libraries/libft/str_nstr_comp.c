/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_nstr_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:07:03 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/13 18:42:39 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_nstr_comp(char *str1, char *str2, size_t size_str2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str2 || !str2[j] || size_str2 <= 0)
		return (str1);
	while (str1 && str1[i])
	{
		if (str1[i + j] == str2[j])
		{
			if (++j == size_str2)
				return (&str1[i]);
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
