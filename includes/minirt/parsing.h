/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:29:52 by npirard           #+#    #+#             */
/*   Updated: 2024/02/25 15:09:05 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <minirt/minirt.h>
# include <minirt/objects.h>


int		scene_open(char *path, t_scene *scene);
void	normalize_scene(t_scene *scene);
char	*skip_space(char **ptr);
bool	parse_cmp(char *ref, char **ptr);

int		scene_parse_line(t_scene *scene, char *line);
int		scene_parse_ambiant(t_scene *scene, int nbr, char **ptr, char *line);
int		scene_parse_light(t_scene *scene, int nbr, char **ptr, char *line);
int		scene_parse_camera(t_scene *scene, int nbr, char **ptr, char *line);

/* --------------------------------- OBJECTS -------------------------------- */

int		scene_parse_object(t_scene *scene, int nbr, char *line);
int		scene_parse_obj_entries(t_object *obj, char **ptr, int nbr, char *line);
int		scene_parse_obj_properties(t_object *object, int nbr,
			char **ptr, char *line);
int		scene_parse_obj_properties2(t_object *object, int nbr,
			char **ptr, char *line);
int		scene_parse_light_obj(char **ptr, t_object *obj);
/* -------------------------------- TEXTURES -------------------------------- */

int		scene_parse_texture(char **ptr, t_object *object, int nbr, char *line);
int		scene_parse_texture_type(char **ptr, t_object *object);
int		scene_parse_texture_solid(char **ptr, t_object *object,
			int nbr, char *line);
int		scene_parse_texture_dame(char **ptr, t_object *object,
			int nbr, char *line);
int		scene_parse_texture_img(char **ptr, t_object *object,
			int nbr, char *line);

/* ---------------------------------- MOVES --------------------------------- */

int		scene_parse_move(t_scene *scene, char **ptr, int nbr, char *line);
int		scene_parse_move_type(char **ptr, t_move *move);
int		scene_parse_move_entries(t_move *move, char **ptr, int nbr, char *line);

/* --------------------------------- VALUES --------------------------------- */

int		scene_parse_type(char **ptr, char *type);
int		scene_parse_origin(char **ptr, t_coord3f *origin);
int		scene_parse_orientation(char **ptr, t_vec3f *orientation);
int		scene_parse_fov(char **ptr, int *fov);
int		scene_parse_ratio(char **ptr, double *ratio);
int		scene_parse_double(char **ptr, double *value);
int		scene_parse_int(char **ptr, int *value);
int		scene_parse_color(char **ptr, t_color3f *color3f);
int		scene_parse_path(char **ptr, char **dest);

/* -------------------------------------------------------------------------- */
/*                                   ERRORS                                   */
/* -------------------------------------------------------------------------- */

void	error_file(char *context, char *path);
void	error_parsing(char *context, int nbr, char *line, char *pos);

#endif
