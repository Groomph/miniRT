/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:34:51 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/21 04:45:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vector.h"

# define BOOL int
# define TRUE 1
# define FALSE 0

typedef struct          s_window_image
{
        void            *img;
        int             *addr;
        int             line_w;
        int             col_h;
        int             bits_pixel;
        int             endian;
	BOOL		set;
}			t_img;

typedef struct          s_camera
{
        t_point         o;
        t_vector        vup;
        double          fov_hori;
        t_point         look_at;
        double          pov_w;
        double          pov_h;
        t_vector        horizontal;
        t_vector        vertical;
        t_point         lower_corner;
}                       t_cam;

typedef struct          s_scene
{
        t_list		*cam_list;
	t_cam		*cam;
//	t_list		*ambiant_light;
//	t_list		light;
        t_list          *object;
//      t_img           *img;           en théorie plus utile, mais peut l'etre si arg > 4
	BOOL		saveit;
}			t_scene;

typedef struct		s_sphere
{
	t_point		o;
	double		radius;
}			t_sphere;

typedef union           u_object_data
{
	t_sphere	sphere;
	int		square;
	unsigned int	triangle;
}			t_data;

typedef struct		s_rayon
{
	t_point		o;
	t_vector	dir;
	int		pixel;
	double		max_t;
	double		t[4];
	t_color		color;
	t_point		hit;
	t_vector	hit_normale;
}			t_ray;

typedef struct		s_object
{
	t_data		data;
	t_color		color;
	BOOL		(*f)(t_ray *ray, t_data *data);
}			t_obj;

void			check_prog_args(t_scene *scene, t_img *img, int ac, char **av);
int			color_microparser(t_color *color, char *format, int *i);
int			fuse_trgb(int t, int r, int g, int b);
int			fuse_vector(t_vector *vec);
int			int_microparser(int *nb, char *format, int *i);
int			double_microparser(double *doub, char *format, int *i);
int			vector_microparser(t_vector *vector, char *format, int *i);

BOOL			add_camera(t_scene *scene, char *format);
void			param_camera(void *temp_cam, void *temp_img);
BOOL			add_sphere(t_scene *scene, char *format);
void			stop_program(t_scene *scene, int errornb, int line);

void			ray_caster(t_scene *scene, t_img *img, void *mlx, void *window);

/*
t_list			*list_new(void *object);
void			list_add_front(t_list **first_link, t_list *new_link);
void			list_add_back(t_list **first_link, t_list *new_link);
int			list_size(t_list *current_link);
t_list			*list_last(t_list *list);
void			list_iter(t_list *list, void (*f)(void *,void *), void *obj);
t_list			*list_map(t_list *list, void *(*f)(void *), void (*del)(void *));
void			list_delone(t_list *list, void (*del)(void*));
void			list_clear(t_list **list, void (*del)(void *));
*/

#endif
