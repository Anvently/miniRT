/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:42:15 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 17:11:57 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/objects.h>
#include <libft.h>

static int	get_random_id(void)
{
	int	id;

	srand(time(NULL));
	id = rand();
	return (id);
}

void	t_object_init(t_object *obj)
{
	obj->k_ambiant = 0.2;
	obj->k_diffuse = 1.0;
	obj->k_specular = 0.2;
	obj->k_plastic = 1.0;
	obj->k_roughness = 1.0;
	obj->k_reflexion = 0.0;
	obj->i_refraction = 1.0;
	obj->texture.type = TEX_SOLID;
	obj->texture.color1 = (t_color3f){1.f, 1.f, 1.f};
	obj->texture.get_color = &texture_get_solid_color;
	obj->orientation = (t_vec3f){0, 1, 0};
	obj->origin = (t_vec3f){2, 0, 0};
	obj->height = 1.f;
	obj->radius = 1.f;
	obj->id = get_random_id();
}
