/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:34:51 by rsanchez          #+#    #+#             */
/*   Updated: 2021/02/12 22:31:43 by rsanchez         ###   ########.fr       */
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
	PLANE,
	TRIANGLE,
	SQUARE,
	SPHERE,
	CYLINDER,
	DISK,
	CUBE
};

enum	e_key
{
	N = 110,
	ESCAPE = 65307,
	UBE
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
	int		anti_aliasing;
	int		recursivity;
	BOOL		gamma;
	struct s_camera	*next;
}			t_cam;

typedef struct		s_light
{
	t_point		o;
	double		intensity;
	t_color		color;
	BOOL		parallel;
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
	double		dist;
}			t_inter;

typedef struct		s_rayon
{
	t_point		o;
	t_vector	dir;
	double		t;
	BOOL		hit_inside;
	double		dist;
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
	t_point		o2;
	t_point		o3;
	t_point		a;
	t_vector	ab;
	t_vector	ad;
	double		radius;
	double		h;
	t_vector	normal;
	BOOL		(*inter_f)(t_ray*, struct s_object*, t_inter*);
	void		(*normal_f)(t_ray*, struct s_object*);
	BOOL		specular;
	BOOL		caps;
	struct s_object	*next;
}			t_obj;

typedef struct		s_scene
{
	void		*mlx;
	void		*window;
	t_cam		*cam_list;
	t_cam		*cam;
	t_light		ambient;
	BOOL		ambient_is_set;
	t_light		*light;
	t_obj		*object;
	t_img		img;
	BOOL		saveit;
}			t_scene;

/****************************************************************
**			    PARSING
****************************************************************/

void			check_prog_args(t_scene *scene, t_img *img, int ac, char **av);
int			add_object(t_scene *scene, char *line, int prev);
int			add_camera(t_scene *scene, char *format);
BOOL			set_resolution(t_scene *scene, t_img *img, char *format);
BOOL			set_ambient_light(t_scene *scene, char *format);
int			add_light(t_scene *scene, char *format);
int			add_plane(t_scene *scene, char *format);
int			add_triangle(t_scene *scene, char *format);
int			add_square(t_scene *scene, char *format);
int			add_sphere(t_scene *scene, char *format);
int			add_cylinder(t_scene *scene, char *format);
int			add_disk(t_scene *scene, t_obj *obj, int i);
BOOL			set_camera_bonus(t_cam *cam, char *format, int i);
BOOL			set_light_bonus(t_light *light, char *format, int i);
//BOOL			set_object_bonus(t_obj *obj, char *format, int i);
int			int_microparser(int *nb, char *format, int *i);
int			double_microparser(double *doub, char *format, int *i);
int			vector_microparser(t_vector *vector, char *format, int *i);
int			color_microparser(t_color *color, char *format, int *i);

void			error_parsing(t_scene *scene, int fd, int errornb, int line);
int			stop_program(t_scene *scene);

void			ray_caster(t_scene *scene, void *mlx, void *window);
void			path_tracer(t_scene *scene, t_ray *ray, int i);
BOOL			is_intersect_sphere(t_ray *ray, t_obj *sphere, t_inter *inter);
BOOL			is_intersect_plane(t_ray *ray, t_obj *plane, t_inter *inter);
BOOL			is_intersect_triangle(t_ray *ray, t_obj *triangle, t_inter *inter);
BOOL			is_intersect_square(t_ray *ray, t_obj *square, t_inter *inter);
BOOL			is_intersect_cylinder(t_ray *ray, t_obj *cylinder, t_inter *inter);
BOOL			is_intersect_disk(t_ray *ray, t_obj *cylinder, t_inter *inter);
void			set_sphere_normal(t_ray *ray, t_obj *sphere);
void			set_plane_normal(t_ray *ray, t_obj *plane);
void			set_triangle_normal(t_ray *ray, t_obj *triangle);
void			set_square_normal(t_ray *ray, t_obj *square);
void			set_cylinder_normal(t_ray *ray, t_obj *cylinder);
void			set_disk_normal(t_ray *ray, t_obj *cylinder);
//void			apply_ambient_light(t_scene *scene, t_ray *ray);
void			apply_light(t_scene *scene, t_ray *ray, t_light *light);
void			apply_light_effects(t_ray *ray, t_light *light, double cos);

void			create_bmp(t_scene *scene, t_img *img);

int			press_key(int key, t_scene *scene);

int			fuse_trgb(int t, int r, int g, int b);
int			fuse_vector(t_vector *vec);

#endif
