NAME		=	minirt
BONUS_NAME	=
TEST		=	test

INCLUDES	=	includes/
SRCS_FOLDER	=	srcs/
OBJS_FOLDER	=	.objs/

SRCS_FILES	=	main.c error.c \
				render/render.c render/fps.c render/image.c render/thread.c \
				render/chunk.c \
				draw/draw.c draw/util.c draw/line.c draw/color_conversion.c \
				draw/color_conversion2.c draw/color_operation.c draw/color_operation2.c \
				events/events.c events/handlers.c events/handlers2.c \
				parsing/parsing.c parsing/parse_line.c parsing/parse_objects.c \
				parsing/parse_value.c parsing/parse_value2.c parsing/normalize.c \
				parsing/parse_objects2.c \
				struct/t_scene.c struct/print.c struct/t_object.c \
				math/geometry_ope.c math/geometry_ope2.c math/cam_rotation.c \
				math/plane_inter.c math/sphere_inter.c math/matrix2.c\
				math/cylinder_inter.c math/cylinder_inter2.c math/get_rot_matrices.c \
				math/cone_inter.c \
				math/equation.c math/multiple.c math/matrix.c math/rotations.c \
				raytracing/camera.c raytracing/rays.c raytracing/transform.c \
				raytracing/light.c

SRCS_TEST = 	math/geometry_ope.c math/geometry_ope2.c \
				math/plane_inter.c math/sphere_inter.c\
				math/cylinder_inter.c math/cylinder_inter2.c \
				math/equation.c math/multiple.c math/matrix.c math/rotations.c \
				math/get_rot_matrices.c math/cam_rotation.c math/matrix2.c \
				struct/print.c \
				mapping/local_base.c mapping/mapping.c

OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
OBJS_TEST	= 	$(addprefix $(OBJS_FOLDER),$(SRCS_TEST:.c=.o))

LIBFT		=	libft/libft.a
LIBMLX		=	libmlx/libmlx.a

HEADERS		=	$(INCLUDES)libft.h $(INCLUDES)mlx.h $(INCLUDES)mlx_int.h \
				$(INCLUDES)$(NAME)/$(NAME).h $(INCLUDES)$(NAME)/draw.h \
				$(INCLUDES)$(NAME)/objects.h $(INCLUDES)$(NAME)/raytracing.h \
				$(INCLUDES)$(NAME)/types.h $(INCLUDES)$(NAME)/calculus.h

DEPS		=	$(LIBFT) $(LIBMLX) $(HEADERS)

CC			=	cc
STATIC_LINK	=	-Llibft/ -lft -Llibmlx/ -lmlx -lXext -lX11 -lm
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)
CFLAGS_OPTI		=	-Wall -Wextra -Werror -O3 -I$(INCLUDES)


.PHONY		=	all clean fclean test re bonus

all: $(NAME)

opti: $(SRCS) $(DEPS)
	@echo "\n-----COMPILING $(NAME)-------\n"
	$(CC) $(CFLAGS_OPTI) $(SRCS) $(STATIC_LINK) -o $(NAME)
	@echo "Executable has been successfully created."

$(NAME): $(DEPS) $(OBJS)
	@echo "\n-----COMPILING $(NAME)-------\n"
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LINK) -o $(NAME)
	@echo "Executable has been successfully created."

$(TEST): $(DEPS) $(OBJS_TEST)
	@echo "\n-----COMPILING $(TEST)-------\n"
	$(CC) $(CFLAGS) $(OBJS_TEST) $(STATIC_LINK) -o $(TEST)
	@echo "Executable has been successfully created."

bonus: $(BONUS_NAME)

$(OBJS_FOLDER)%.o: $(SRCS_FOLDER)%.c Makefile $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(INCLUDES)libft.h: libft/libft.h
	@echo "------ UPDATING LIBFT HEADER -------\n"
	cp libft/libft.h $(INCLUDES)libft.h

$(INCLUDES)mlx.h: libmlx/mlx.h
	@echo "------ UPDATING MLX HEADER -------\n"
	cp libmlx/mlx.h $(INCLUDES)mlx.h

$(INCLUDES)mlx_int.h: libmlx/mlx_int.h
	@echo "------ UPDATING MLX HEADER -------\n"
	cp libmlx/mlx_int.h $(INCLUDES)mlx_int.h

$(LIBFT): $(INCLUDES)libft.h
	@echo "\n-------COMPILING LIBFT--------------\n"
	make -C libft/
	make clean -C libft/
	@echo "\n\n"

$(LIBMLX): $(INCLUDES)mlx.h
	@echo "\n-------COMPILING MINILIBX--------------\n"
	make -C libmlx/
	@echo "\n\n"


clean:
	@echo "\n-------------CLEAN--------------\n"
	make clean -C libft/
	make clean -C libmlx/
	rm -rf $(OBJS_FOLDER)
	@echo "object files have been removed."

fclean: clean
	@echo "\n-------------FORCE CLEAN--------------\n"
	make fclean -C libft/
	rm -rf $(NAME) $(BONUS_NAME) $(TEST)
	@echo "$(NAME) and object files have been removed."

re: fclean all
