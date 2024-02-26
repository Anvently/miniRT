/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:07:32 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 14:37:15 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

static void	exec_move(t_scene *scene, t_move *move, double render_time)
{
	t_matrix3f	matrix;
	double		factor;

	factor = render_time * move->speed;
	if (move->type == MV_R)
	{
		matrix = matrix_rotate(factor * move->value.x, factor * move->value.y, \
			factor * move->value.z);
		transform_objects(scene->data, &matrix, 0.f, move->target);
	}
	else if (move->type == MV_Rs)
		transform_objects(scene->data, NULL, \
			factor * move->value.z, move->target);
}

void	scene_move(t_scene *scene, double render_time)
{
	t_list	*node;
	t_move	*move;

	node = scene->moves;
	while (node)
	{
		move = (t_move *)node->content;
		exec_move(scene, move, render_time);
		node = node->next;
	}
}
