/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:42:15 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 17:44:56 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <libft.h>

void	t_object_init(t_object *obj)
{
	obj->k_ambiant = 1.0;
	obj->k_diffuse = 1.0;
	obj->k_specular = 1.0;
	obj->k_plastic = 1.0;
	obj->k_roughness = 1.0;
	obj->k_reflexion = 0.0;
}
