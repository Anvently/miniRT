/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:48:05 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/15 16:07:18 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

#include <math.h>
# include <minirt/types.h>

/*-------GEOMETRY OPE-------*/
double		scalar_product(t_vec3f *t_u, t_vec3f *t_v);
void		normalize_vec(t_vec3f *t_u);
t_vec3f		vector_product(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_sum(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_diff(t_vec3f *t_u, t_vec3f *t_v);
t_vec3f		vec3_scale(t_vec3f *vector, double scale);
double	distance(t_vec3f *a, t_vec3f *b);

/*--------EQUATION*/
int	quadra_solver(double a, double b, double c, double *t);
int	linear_solver(double a, double b, double *t);
t_vec3f	get_inter_point(t_ray *ray, double t);
void	display_vector(t_vec3f	*vec);
/*-----PLANE----------*/
void	plane_intersec(t_object *plane, t_ray *ray);
/*-------SPHERE----------------*/
void	sphere_intersec(t_object *sphere, t_ray *ray);
/*------------CYLINDER-----------------*/
int	top_cap_intersec(t_object *cyld, t_ray *ray, double *t);
int	bot_cap_intersec(t_object *cyld, t_ray *ray, double *t);
void	cylinder_intersec(t_object *cylinder, t_ray *ray);

/* ------------------------------ MULTIPLE OPE ------------------------------ */

int		get_sup_multiple(int n, int comp, int max);
int		get_inf_multiple(int n, int comp);

#endif
