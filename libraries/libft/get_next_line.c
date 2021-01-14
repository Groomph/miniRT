/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:48:15 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/24 19:45:47 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static size_t	isnl(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static int	extractline(char **buf, char **line, size_t nl, size_t len)
{
	if (len == 0)
	{
		if (*buf)
		{
			*line = *buf;
			*buf = NULL;
			return (0);
		}
		if (!(*line = malloc(1)))
			return (-1);
		**line = '\0';
		return (0);
	}
	*line = substr_free(*buf, 0, nl, DONTFREE);
	*buf = substr_free(*buf, nl + 1, 100, DOFREE);
	if (!*line || !*buf)
		return (-1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*permbuf;
	char		tmpbuf[101];
	size_t		len;
	size_t		nl;

	if (fd < 0 || read(fd, 0, 0) < 0 || !line)
		return (-1);
	len = 1;
	nl = isnl(permbuf);
	while (nl == 0 && len)
	{
		len = read(fd, tmpbuf, 100);
		if (len)
		{
			tmpbuf[len] = '\0';
			permbuf = strjoin_free(permbuf, tmpbuf,
							DOFREE, DONTFREE);
			if (!permbuf)
				return (-1);
			nl = isnl(permbuf);
		}
	}
	return (extractline(&permbuf, line, nl - 1, len));
}
