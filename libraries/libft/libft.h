/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:25:29 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/29 11:42:29 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# define DOFREE 1
# define DONTFREE 0

typedef struct		s_list
{
	void		*object;
	struct s_list	*next;
}			t_list;

/*
 ******************   BYTEWISE & MEMORY  ******************
*/

void			init_zero(void *pt, size_t i);

/*
 *******************  IS? FONCTIONS  *******************
*/

int			is_double_signed(long double doub);
int			is_not_number(long double doub);
int			is_infinite(long double doub);

/*
 *******************  CHAR & STRING  *******************
*/

char			*substr_free(char *s, size_t start, size_t len, int freestr);
char			*strjoin_free(char *s1, char *s2, int freestr1, int freestr2);
size_t			string_len(const char *s);
int			shift_right_add(char *str, char c, int i);
int			shift_left_erase(char *str, int i);
int			str_n_comp(char *str, char *str2, int stop);
char			*str_nstr_comp(char *str1, char *str2, size_t size_str2);

int			utoa_len(unsigned long long nb, int sizebase);
int			utoa_base(unsigned long long nb, char *dest,
								char *base, int sizebase);
int			atoi_windex(const char *str, int *i);
double			atodoub_windex(const char *str, int *i);

/*
 *******************  LINKED LIST  *******************
*/

/*
 *******************  FILE DESCRIPTOR  *******************
*/

int			get_next_line(int fd, char **line);

#endif
