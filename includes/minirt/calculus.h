/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:48:05 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/19 13:37:31 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULUS_H
# define CALCULUS_H

# include <math.h>
# include <minirt/types.h>

typedef struct s_matrix4f {
	double		m1[4];
	double		m2[4];
	double		m0[4];
	double		m3[4];
}				t_matrix4f;

typedef struct s_matrix3f {
	double		m0[3];
	double		m1[3];
	double		m2[3];
}				t_matrix3f;

/*-------GEOMETRY OPE-------*/
double		scalar_product(t_vec3f *t_u, t_vec3f *t_v);
void		normalize_vec(t_vec3f *t_u);
t_vec3f		vector_product(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_sum(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_diff(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_scale(t_vec3f *vector, double scale);
t_vec3f		vec3f_matrix(t_vec3f *vec, t_matrix4f *matrix);
double		distance(t_vec3f *a, t_vec3f *b);

/*--------EQUATION*/
int			quadra_solver(double a, double b, double c, double *t);
int			linear_solver(double a, double b, double *t);
t_vec3f		get_inter_point(t_ray *ray, double t);
void		display_vector(t_vec3f	*vec);
/*-----PLANE----------*/
void		plane_intersec(t_object *plane, t_ray *ray);
/*-------SPHERE----------------*/
void		sphere_intersec(t_object *sphere, t_ray *ray);
/*------------CYLINDER-----------------*/
int			top_cap_intersec(t_object *cyld, t_ray *ray, double *t);
int			bot_cap_intersec(t_object *cyld, t_ray *ray, double *t);
void		cylinder_intersec(t_object *cylinder, t_ray *ray);

/* --------------------------------- MATRIX --------------------------------- */

t_vec3f		vec3f_rotate(t_vec3f *vec, double x, double y, double z);
t_matrix4f	matrix_rotate(double x, double y, double z);
t_matrix3f	matrix_sum(t_matrix3f *a, t_matrix3f *b);
t_vec3f	vec3f_mat3(t_vec3f *vec, t_matrix3f *matrix);
void		display_matrix(t_matrix3f *m);

/* ------------------------------ MULTIPLE OPE ------------------------------ */

int			get_sup_multiple(int n, int comp, int max);
int			get_inf_multiple(int n, int comp);

/*---------------GET_ROT_MATRIX-----------------------*/
t_matrix3f	rotation_matrix(t_vec3f	*cam_dir);

#endif
