#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

NAME		=	minishell
LIBFT		=	libft.a
LDIR		=	libft/
HISTORYLIB	=	readline/libhistory.a
READLINELIB	=	readline/libreadline.a

# Style
BOLD		=	\033[1m
ITALIC		=	\033[3m
UNDERLINE	=	\033[4m

# Color text
RESET		=	\033[0m
BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
PURPLE		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
DEFAULT		=	\033[39m
ERASE_LINE	=	\033[2K\r

# Compiler and flags
CC			=	gcc -g
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf

# Sources are all .c files
SRCS		=	minishell.c\
				minishell_utils.c\
				path.c\
				io_redirection.c\
				list.c\
				pipe.c\
				parsing.c\
				signal_handler.c\

OBJS_DIR	=	obj/
OBJS_LST	=	$(patsubst %.c, %.o, $(SRCS))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: dir $(NAME)

# Generates output file
$(NAME): $(OBJS)
	@cd LIBFT/ && make && cd ..
	@$(CC) $(CFLAGS) src/*/*.c $(LDIR)$(LIBFT) -l readline -l ncurses \
	$(HISTORYLIB) $(READLINELIB) -o $(NAME)
	@echo "$(ERASE_LINE)$(GREEN)✔️ $(ITALIC)Minishell successfully compile.$(RESET)\
	$(GREEN) ✔️$(RESET)"

# Compiles sources into objects
$(OBJS_DIR)%.o: src/*/%.c
	@printf "$(ERASE_LINE)⚙️ $(PURPLE)Compiling $(DEFAULT)⚙️$(YELLOW) $(notdir $<)\
	$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# create objects directory
dir:
	@mkdir -p $(OBJS_DIR)

# Removes objects
clean:
	@cd LIBFT/ && make clean && cd ..
	@printf "💣 $(RED)Removing minishell objects...$(RESET) 💥\n"
	@$(RM) $(OBJS_DIR)

# Removes objects and executables
fclean: clean
	@printf "💣 $(RED)Removing libft executable$(RESET) 💥\n"
	@$(RM) $(LDIR)$(LIBFT)
	@printf "💣 $(RED)Removing minishell executable$(RESET) 💥\n"
	@$(RM) $(NAME)

# Removes objects and executables and remakes
re: fclean all
	@echo "$(ERASE_LINE)$(GREEN)✔️ $(ITALIC)Remake complete$(RESET)\
	$(GREEN) ✔️$(RESET)"

run: all
	@./minishell
