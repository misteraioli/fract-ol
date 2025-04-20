#######################################################
## ARGUMENTS

# NAME

NAME		=	fractol
NAME_BONUS	=	$(addsuffix _bonus, $(NAME))

# CC FLAG INC

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-Iinc -Iminilibx-linux

# SRC & OBJ DIR

SRC_DIR			=	src/
OBJ_DIR			=	obj/

SRC_DIR_BONUS	=	src_bonus/
OBJ_DIR_BONUS	=	obj_bonus/

# LIB

LIBX_PATH	=	./minilibx-linux
LIBFT_PATH	=	./libft

LIBX		=	$(LIBX_PATH)/libmlx_Linux.a -lXext -lX11 -lm -lz
LIBFT		=	$(LIBFT_PATH)/libft.a

# RM

RM	=	rm -rf

# HEADERS

HEADER	= \
		inc/fractol.h \
		inc/fractol_bonus.h \

#######################################################
## SRCS & OBJS

FILES		= \
			main \
			init \
			events \
			render \
			utils \

SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

SRCS_BONUS	=	$(addprefix $(SRC_DIR_BONUS), $(addsuffix _bonus.c, $(FILES)))
OBJS_BONUS	=	$(addprefix $(OBJ_DIR_BONUS), $(addsuffix _bonus.o, $(FILES)))

#######################################################
## RULES

all : $(LIBX) $(LIBFT) $(NAME)

$(LIBFT) :
		make -C $(LIBFT_PATH)

$(LIBX) :
		make -C $(LIBX_PATH)

$(NAME) : $(OBJ_DIR) $(OBJS) Makefile
		$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME) $(LIBX) $(LIBFT)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus : all $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_DIR_BONUS) $(OBJS_BONUS)
		$(CC) $(CFLAGS) $(INC) $(OBJS_BONUS) -o $(NAME_BONUS) $(LIBX) $(LIBFT)

$(OBJ_DIR_BONUS):
		@mkdir -p $(OBJ_DIR_BONUS)

$(OBJ_DIR_BONUS)%.o : $(SRC_DIR_BONUS)%.c $(HEADER)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

norm :
	norminette libft inc src src_bonus

clean :
		@make -C $(LIBX_PATH) clean
		@make -C $(LIBFT_PATH) fclean
		$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean : clean
		$(RM) $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: all clean fclean re bonus norm
