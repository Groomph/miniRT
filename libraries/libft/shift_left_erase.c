/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_left_erase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:26:41 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:26:48 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	shift_left_erase(char *str, int i)
{
	if (!str)
		return (-1);
	str[i] = str[i + 1];
	if (str[i])
		return (shift_left_erase(str, i + 1));
	else
		return (i);
}
