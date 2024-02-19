/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:48:05 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/19 18:44:48 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULUS_H
# define CALCULUS_H

# include <math.h>
# include <minirt/types.h>

/*-------GEOMETRY OPE-------*/
double		scalar_product(t_vec3f *t_u, t_vec3f *t_v);
void		normalize_vec(t_vec3f *t_u);
t_vec3f		vector_product(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_sum(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_diff(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_scale(t_vec3f *vector, double scale);
t_vec3f		vec3f_matrix4f(t_vec3f *vec, t_matrix4f *matrix);
double		distance(t_vec3f *a, t_vec3f *b);
t_vec3f		vec3f_get_dir(t_coord3f *a, t_coord3f *b);

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
t_matrix3f	matrix_rotate(double x, double y, double z);
t_matrix3f	matrix_sum(t_matrix3f *a, t_matrix3f *b);
t_matrix3f	matrix_transpose(t_matrix3f *m);
t_vec3f		vec3f_matrix3f(t_vec3f *vec, t_matrix3f *matrix);
void		display_matrix(t_matrix3f *m);

/* ------------------------------ MULTIPLE OPE ------------------------------ */

int			get_sup_multiple(int n, int comp, int max);
int			get_inf_multiple(int n, int comp);

/*---------------GET_ROT_MATRIX-----------------------*/
t_matrix3f	rotation_matrix(t_vec3f	*cam_dir);

#endif
