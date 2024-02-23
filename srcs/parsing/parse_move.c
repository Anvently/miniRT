/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 17:52:50 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>
#include <minirt/calculus.h>

int	scene_parse_move_type(char **ptr, t_move *move)
{
	skip_space(ptr);
	if (!**ptr)
		return (1);
	if (parse_cmp("R", ptr))
		move->type = MV_R;
	else if (parse_cmp("T", ptr))
		move->type = MV_T;
	else if (parse_cmp("S", ptr))
		move->type = MV_S;
	else
		return (1);
	return (0);
}

int	scene_parse_move(t_scene *scene, char **ptr, int nbr, char *line)
{
	t_list		*move_node;
	t_move		*move;

	move = ft_calloc(1, sizeof(t_move));
	if (!move)
		return (error("parsing move"), 1);
	move_node = ft_lstnew(move);
	if (!move_node)
		return (free(move), error("parsing move"), 1);
	ft_lstadd_back(&scene->moves, move_node);
	if (scene_parse_move_entries(move, ptr, nbr, line))
		return (1);
	return (0);
}

int	scene_parse_move_entries(t_move *move, char **ptr, int nbr, char *line)
{
	while (**ptr)
	{
		if (*skip_space(ptr) == '\0')
			break ;
		if (parse_cmp("type:", ptr) && scene_parse_move_type(ptr, move))
			return (error_parsing("move type", nbr, line, NULL), 1);
		else if (parse_cmp("value:", ptr)
			&& scene_parse_origin(ptr, &move->value))
			return (error_parsing("move value", nbr, line, NULL), 1);
		else if (parse_cmp("target:", ptr)
			&& (scene_parse_int(ptr, &move->target) || move->target < 0))
			return (error_parsing("move target", nbr, line, NULL), 1);
		else if (parse_cmp("speed:", ptr)
			&& (scene_parse_double(ptr, &move->speed) || move->speed < 0.f))
			return (error_parsing("move speed", nbr, line, NULL), 1);
		else if (**ptr && ft_isspace(**ptr) == false)
			return (error_parsing("unknown property", nbr, line, *ptr), 1);
	}
	return (0);
}
