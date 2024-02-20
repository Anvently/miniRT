/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:18:35 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/20 14:45:41 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt/calculus.h"
#include "../../includes/minirt/types.h"

/// @brief find the eventual positivive solution of the equation at + b = 0
/// @param a the linear term
/// @param b the constant term
/// @return 1 if there is a solution and 0 if there is not
int	linear_solver(double a, double b, double *t)
{
	double	res;

	if (a == 0 && b)
		return (0);
	res = -b / a;
	if (res >= 0)
	{
		*t = res;
		return (1);
	}
	else
		return (0);
}
/// @brief Find the eventual solution of at^2 + bt + c = 0 and keeps the smallest positive one
/// @param a the quadratic term
/// @param b the linear term
/// @param c the constant term
/// @param t a pointer to store the smallest positive solution if it exists
/// @return 0 if there's no solution or both are negative, 1 otherwise
int	quadra_solver(double a, double b, double c, double *t)
{
	double	delta;
	double	half_b;
	double	sol1;
	double	sol2;

	if (a == 0)
		return (linear_solver(b, c, t));
	half_b = 0.5f * b / a;
	c = c / a;
	delta = half_b * half_b - c;
	if (delta < 0)
		return (0);
	sol1 = - half_b + sqrt(delta);
	sol2 = - 2 * half_b - sol1;
	if ( c >= 0 && sol1 >= 0 && sol2 >= 1)
		*t = sol2;
	else if (c >= 0 && sol1 >= 0 && sol2 < 1)
		*t = sol1;
	else if (c >= 0 && sol1 < 0)
		return (0);
	else if (c < 0 && sol1 > 0)
		*t = sol1;
	return (1);
}

t_vec3f	get_inter_point(t_ray *ray, double t)
{
	t_vec3f	impact;

	impact.x = ray->origin.x + ray->dir.x * t;
	impact.y = ray->origin.y + ray->dir.y * t;
	impact.z = ray->origin.z + ray->dir.z * t;
	return (impact);
}

void	display_vector(t_vec3f	*vec)
{
	printf("x:%f || y:%f || z:%f\n", vec->x, vec->y, vec->z);
}
