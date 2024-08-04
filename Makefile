#######################################################
## ARGUMENTS

NAME		=	fractol

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
HEADER		=	-Iinc

SRC_DIR		=	src/
OBJ_DIR		=	obj/

LIB_PATH	=	./libft
LIB			=	$(LIB_PATH)/libft.a

RM			=	rm -rf

#######################################################
## SRCS & OBJS

FILES		= \
			main \
			init \
			events \
			render \
			utils \

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

#######################################################
## RULES

all : make_lib $(NAME)

make_lib :
		make -C $(LIB_PATH)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(HEADER) $(LIB) -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) $(HEADER) -Iminilibx-linux -O3 -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

clean :
		make -C $(LIB_PATH) fclean
		$(RM) $(OBJ_DIR)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
