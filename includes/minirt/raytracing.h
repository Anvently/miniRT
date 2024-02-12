/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:44:30 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 14:50:37 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <minirt/minirt.h>

typedef t_int2	t_vec2i;
typedef t_int3	t_vec3i;

typedef struct s_vec2f {
	float		x;
	float		y;
}				t_vec2f;

typedef struct s_vec3f {
	float		x;
	float		y;
	float		z;
}				t_vec3f;

#endif