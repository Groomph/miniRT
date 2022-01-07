/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:34:51 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/07 16:47:42 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vector.h"
# include <pthread.h>

# define BOOL int
# define TRUE 1
# define FALSE 0

enum	e_type_object
{
	PLANE,
	TRIANGLE,
	CYLINDER,
	SQUARE,
	PYRAMIDE,
	CUBE,
	SPHERE,
	DISK,
	CONE
};

enum	e_key
{
	N = 110,
	ESCAPE = 65307,
	PLUS = 65451,
	MINUS = 65453,
	UP = 65362,
	DOWN = 65364,
	RIGHT = 65361,
	LEFT = 65363,
	Z = 122,
	S = 115,
	Q = 113,
	D = 100,
	CTRL = 65507,
	SPACE = 32,
	A = 97,
	E = 101,
	TAB = 65289,
	R = 114,
	T = 116,
	ENTER = 65293
};

typedef struct s_window_image
{
	void	*img;
	int		*addr;
	int		line_w;
	int		col_h;
	int		bits_pixel;
	int		endian;
	BOOL	set;
}		t_img;

typedef struct s_camera	t_cam;

typedef struct s_camera
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
	int			anti_aliasing;
	int			recursivity;
	BOOL		gamma;
	t_cam		*next;
}			t_cam;

typedef struct s_light	t_light;

typedef struct s_light
{
	t_point		o;
	double		intensity;
	t_color		color;
	BOOL		parallel;
	t_light		*next;
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

typedef struct s_intersection
{
	double	t1;
	double	t2;
	BOOL	hit_inside;
	double	dist;
}		t_inter;

typedef struct s_object	t_obj;

typedef struct s_rayon
{
	t_point		o;
	t_vector	dir;
	double		t;
	BOOL		hit_inside;
	double		dist;
	t_color		color;
	t_color		temp_color;
	t_obj		*nearest_object;
	t_point		hit;
	t_vector	hit_normal;
}			t_ray;

typedef struct s_object
{
	t_point		o;
	t_vector	normal;
	double		radius;
	t_color		color;
	int			type;
	t_point		o2;
	t_point		o3;
	t_point		a;
	t_point		b;
	t_point		c;
	t_point		d;
	t_vector	ab;
	t_vector	ad;
	double		h;
	int			(*inter_f)(t_ray *ray, t_obj *obj, t_inter *inter);
	void		(*normal_f)(t_ray *ray, t_obj *obj);
	t_obj		*main;
	BOOL		specular;
	BOOL		caps;
	BOOL		check_board;
	BOOL		rainbow;
	BOOL		perlin;
	BOOL		marbre;
	BOOL		liana;
	BOOL		wave;
	BOOL		water;
	t_obj		*next;
}			t_obj;

typedef struct s_controler
{
	int		coef;
	t_obj	*selected_obj;
}		t_control;

typedef struct s_thread
{
	struct s_scene	*scene;
	int				y;
	int				max_y;
	int				pixel;
	int				id;
}			t_thread;

typedef struct s_sky_box
{
	t_point		o;
	t_vector	normal;
	t_point		a;
	t_vector	ab;
	t_vector	ad;
	double		radius;
	int			w;
	int			h;
	void		*img;
	int			*addr;
}			t_sky_box;

typedef struct s_scene
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
	t_sky_box	skybox[6];
	BOOL		box;
	BOOL		saveit;
	t_control	control;
	int			thread_total;
}			t_scene;

void				check_prog_args(t_scene *scene, t_img *img, int ac,
						char **av);
int					add_object(t_scene *scene, char *line, int prev);
int					add_camera(t_scene *scene, char *format);
BOOL				set_resolution(t_scene *scene, t_img *img, char *format);
BOOL				set_ambient_light(t_scene *scene, char *format);
int					add_light(t_scene *scene, char *format);
int					add_plane(t_scene *scene, char *format);
int					add_triangle(t_scene *scene, char *format);
int					add_square(t_scene *scene, char *format);
int					add_sphere(t_scene *scene, char *format);
int					add_cylinder(t_scene *scene, char *format);
int					add_disk(t_scene *scene, t_obj *obj, int i);
int					add_cube(t_scene *scene, char *format);
int					add_pyramide(t_scene *scene, char *format);
int					add_cone(t_scene *scene, char *format);
int					add_sky_box(t_scene *scene, char *format);
void				set_edges(t_obj *square);
void				reset_cube(t_obj *first);
void				reset_new_triangle(t_obj *first);
void				reset_disk(t_obj *first);
int					add_bonus(t_scene *scene, char *format, int previous);
BOOL				set_camera_bonus(t_cam *cam, char *format, int i);
BOOL				set_light_bonus(t_light *light, char *format, int i);
BOOL				set_multi_threading(t_scene *scene, char *format);
int					int_microparser(int *nb, char *format, int *i);
int					double_microparser(double *doub, char *format, int *i);
int					vector_microparser(t_vector *vector, char *format, int *i);
int					color_microparser(t_color *color, char *format, int *i);

void				error_parsing(t_scene *scene, int fd, int errornb,
						int line);
int					stop_program(t_scene *scene);

void				set_ray(t_scene *scene, t_ray *ray, double x, double y);
void				*ray_caster(void *thread);
void				path_tracer(t_scene *scene, t_ray *ray, int i);
BOOL				find_nearest_object(t_scene *scene, t_ray *ray);
BOOL				is_intersect_sphere(t_ray *ray, t_obj *sphere,
						t_inter *inter);
BOOL				is_intersect_plane(t_ray *ray, t_obj *plane,
						t_inter *inter);
BOOL				is_intersect_triangle(t_ray *ray, t_obj *triangle,
						t_inter *inter);
BOOL				is_intersect_square(t_ray *ray, t_obj *square,
						t_inter *inter);
BOOL				is_intersect_cylinder(t_ray *ray, t_obj *cylinder,
						t_inter *inter);
BOOL				is_intersect_disk(t_ray *ray, t_obj *cylinder,
						t_inter *inter);
BOOL				is_intersect_cone(t_ray *ray, t_obj *cone, t_inter *inter);
void				set_sphere_normal(t_ray *ray, t_obj *sphere);
void				set_plane_normal(t_ray *ray, t_obj *plane);
void				set_triangle_normal(t_ray *ray, t_obj *triangle);
void				set_square_normal(t_ray *ray, t_obj *square);
void				set_cylinder_normal(t_ray *ray, t_obj *cylinder);
void				set_disk_normal(t_ray *ray, t_obj *cylinder);
void				set_cone_normal(t_ray *ray, t_obj *cone);
void				apply_light(t_scene *scene, t_ray *ray, t_light *light);
void				apply_light_effects(t_ray *ray, t_light *light, double cos);
void				check_board(t_ray *ray);
void				rainbow(t_ray *ray, int type);
void				perlin(t_point p, t_color *c);
double				noise(double x, double y, double z);
void				marbre(t_point p, t_color *c);
void				liana(t_point p, t_color *c);
void				water(t_point *p, t_vector *normal);
void				wave(t_point *p, t_vector *normal);
void				skybox_intersect(t_scene *scene, t_ray *ray);

void				create_bmp(t_scene *scene, t_img *img);

int					press_key(int key, t_scene *scene);
int					press_mouse_button(int key, int x, int y, t_scene *scene);
void				translat_lobby(t_scene *scene, int key, t_obj *obj);
void				rotate_lobby(t_scene *scene, int key);
void				param_camera(t_cam *cam, double w, double h);
void				set_threads_number(t_scene *scene, int key);
void				set_coef(t_control *control, int key);
void				launch_threads(t_scene *scene);

int					fuse_trgb(int t, int r, int g, int b);
int					fuse_vector(t_vector *vec);

#endif
