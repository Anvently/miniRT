/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:45:48 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 18:58:40 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <libft.h>
#include <minirt/objects.h>

void	*t_scene_free(t_scene **scene)
{
	ft_lstclear(&(*scene)->objects, NULL);
	ft_lstclear(&(*scene)->lights, NULL);
	free(*scene);
	*scene = NULL;
	return (NULL);
}
