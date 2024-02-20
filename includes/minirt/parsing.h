/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:29:52 by npirard           #+#    #+#             */
/*   Updated: 2024/02/20 14:40:17 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <minirt/minirt.h>
# include <minirt/objects.h>


int		scene_open(char *path, t_scene *scene);
void	normalize_scene(t_scene *scene);

int		scene_parse_line(t_scene *scene, char *line);
int		scene_parse_ambiant(t_scene *scene, int nbr, char **ptr, char *line);
int		scene_parse_light(t_scene *scene, int nbr, char **ptr, char *line);
int		scene_parse_camera(t_scene *scene, int nbr, char **ptr, char *line);

/* --------------------------------- OBJECTS -------------------------------- */

int		scene_parse_object(t_scene *scene, int nbr, char *line);
int		scene_parse_sphere(t_object *object, int nbr, char **ptr, char *line);
int		scene_parse_plan(t_object *object, int nbr, char **ptr, char *line);
int		scene_parse_cylinder(t_object *object, int nbr, char **ptr, char *line);
int		scene_parse_obj_properties(t_object *object, int nbr,
			char *ptr, char *line);

/* --------------------------------- VALUES --------------------------------- */

int		scene_parse_type(char **ptr, char *type);
int		scene_parse_origin(char **ptr, t_coord3f *origin);
int		scene_parse_orientation(char **ptr, t_vec3f *orientation);
int		scene_parse_fov(char **ptr, int *fov);
int		scene_parse_ratio(char **ptr, double *ratio);
int		scene_parse_double(char **ptr, double *value);
int		scene_parse_color(char **ptr, t_color3f *color3f);

/* -------------------------------------------------------------------------- */
/*                                   ERRORS                                   */
/* -------------------------------------------------------------------------- */

void	error_file(char *context, char *path);
void	error_parsing(char *context, int nbr, char *line);

#endif