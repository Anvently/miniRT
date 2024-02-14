NAME		=	minirt
BONUS_NAME	=

INCLUDES	=	includes/
SRCS_FOLDER	=	srcs/
OBJS_FOLDER	=	.objs/

SRCS_FILES	=	main.c error.c \
				render/render.c render/fps.c render/image.c render/thread.c \
				draw/draw.c draw/util.c draw/line.c draw/color.c draw/color2.c \
				events/events.c events/handlers.c \
				parsing/parsing.c parsing/parse_line.c parsing/parse_objects.c \
				parsing/parse_value.c parsing/parse_value2.c \
				struct/t_scene.c struct/print.c \
				math/geometry_ope.c \
				raytracing/camera.c raytracing/rays.c

OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))

LIBFT		=	libft/libft.a
LIBMLX		=	libmlx/libmlx.a

HEADERS		=	$(INCLUDES)libft.h $(INCLUDES)mlx.h $(INCLUDES)mlx_int.h \
				$(INCLUDES)$(NAME)/$(NAME).h $(INCLUDES)$(NAME)/draw.h \
				$(INCLUDES)$(NAME)/objects.h $(INCLUDES)$(NAME)/raytracing.h

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
	rm -rf $(NAME) $(BONUS_NAME)
	@echo "$(NAME) and object files have been removed."

re: fclean all
