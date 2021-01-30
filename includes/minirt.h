/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:34:51 by rsanchez          #+#    #+#             */
/*   Updated: 2021/01/29 21:59:01 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vector.h"

# define BOOL int
# define TRUE 1
# define FALSE 0

enum	e_type_object
{
	SPHERE,
	CARRE,
	TRIANGLE,
	PLANE,
	CYLINDER
};

typedef struct		s_window_image
{
	void		*img;
	int		*addr;
	int		line_w;
	int		col_h;
	int		bits_pixel;
	int		endian;
	BOOL		set;
}			t_img;

typedef struct		s_camera
{
	t_point		o;
	t_vector	vup;
	double		fov_hori;
	t_point		look_at;
	double		pov_w;
	double		pov_h;
	t_vector	horizontal;
	t_vector	vertical;
	t_point		lower_corner;
	struct s_camera	*next;
}			t_cam;

typedef struct		s_light
{
	t_point		o;
	double		intensity;
	t_color		color;
	struct s_light	*next;
}			t_light;

/*
**typedef union           u_object_data
**{
**	t_light		light;
**	t_sphere	sphere;
**	int		square;
**	unsigned int	triangle;
**}			t_data;
*/

typedef struct		s_intersection
{
	double		t1;
	double		t2;
	BOOL		hit_inside;
}			t_inter;

typedef struct		s_rayon
{
	t_point		o;
	t_vector	dir;
	double		t;
	BOOL		hit_inside;
	t_color		color;
	struct s_object	*nearest_object;
	t_point		hit;
	t_vector	hit_normal;
}			t_ray;

typedef struct		s_object
{
	t_color		color;
	int		type;
	t_point		o;
	double		radius;
	BOOL		(*inter_f)(t_ray*, struct s_object*, t_inter*);
	void		(*normal_f)(t_ray*, struct s_object*);
	struct s_object	*next;
}			t_obj;

typedef struct		s_scene
{
	t_cam		*cam_list;
	t_cam		*cam;
	t_color		ambient_light;
	double		ambient_intensity;
	BOOL		ambient_is_set;
	t_light		*light;
	t_obj		*object;
	t_img		img;
	BOOL		saveit;
}			t_scene;

void			check_prog_args(t_scene *scene, t_img *img, int ac, char **av);
int			color_microparser(t_color *color, char *format, int *i);
int			fuse_trgb(int t, int r, int g, int b);
int			fuse_vector(t_vector *vec);
int			int_microparser(int *nb, char *format, int *i);
int			double_microparser(double *doub, char *format, int *i);
int			vector_microparser(t_vector *vector, char *format, int *i);

int			add_camera(t_scene *scene, char *format);
void			param_camera(t_cam *cam, double w, double h);
int			add_light(t_scene *scene, char *format);
int			add_sphere(t_scene *scene, char *format);
void			stop_program(t_scene *scene, int errornb, int line);

void			ray_caster(t_scene *scene, void *mlx, void *window);
int			path_tracer(t_scene *scene, t_ray *ray, void *ignore, int i);
BOOL			find_nearest_object(t_scene *scene, t_ray *ray, void *ignore);
BOOL			is_intercept_sphere(t_ray *ray, t_obj *sphere, t_inter *inter);
BOOL			is_intercept_sphere2(t_ray *ray, t_obj *sphere);
void			set_sphere_normal(t_ray *ray, t_obj *sphere);
void			apply_ambient_light(t_scene *scene, t_ray *ray);
void			apply_light(t_scene *scene, t_light *light, t_ray *ray);

#endif
