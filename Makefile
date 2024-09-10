#######################################################
## ARGUMENTS

NAME			=	fractol
NAME_BONUS		=	$(addsuffix _bonus, $(NAME))

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
HEADER			=	-Iinc -Iminilibx-linux

SRC_DIR			=	src/
OBJ_DIR			=	obj/

SRC_DIR_BONUS	=	src_bonus/
OBJ_DIR_BONUS	=	obj_bonus/

LIBX_PATH		=	./minilibx-linux
LIBFT_PATH		=	./libft
LIBX			=	$(LIBX_PATH)/libmlx_Linux.a -lXext -lX11 -lm -lz
LIBFT			=	$(LIBFT_PATH)/libft.a

RM				=	rm -rf

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

all : $(NAME)

$(LIBFT) :
		make -C $(LIBFT_PATH)

$(LIBX) :
		make -C $(LIBX_PATH)

$(NAME) : $(LIBX) $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(HEADER) -o $(NAME) $(LIBX) $(LIBFT)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

bonus : all $(NAME_BONUS)

$(NAME_BONUS) : $(OBJS_BONUS)
		$(CC) $(CFLAGS) $(OBJS_BONUS) $(HEADER) -o $(NAME_BONUS) $(LIBX) $(LIBFT)

$(OBJ_DIR_BONUS)%.o : $(SRC_DIR_BONUS)%.c | $(OBJ_DIR_BONUS)
		$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR_BONUS):
		@mkdir -p $(OBJ_DIR_BONUS)

norm :
	norminette libft inc src src_bonus

clean :
		@make -C $(LIBX_PATH) clean
		@make -C $(LIBFT_PATH) clean
		$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean : clean
		@make -C $(LIBFT_PATH) fclean
		$(RM) $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: all clean fclean bonus norm re
