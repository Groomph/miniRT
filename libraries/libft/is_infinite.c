/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_infinite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:24:45 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:24:49 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_infinite(long double doub)
{
	unsigned int	up;
	float			inf;

	up = 0xFF800000;
	inf = *(float *)&up;
	if (doub == inf)
		return (-1);
	up = 0x7F800000;
	inf = *(float *)&up;
	if (doub == inf)
		return (1);
	return (0);
}
