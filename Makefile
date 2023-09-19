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
# base_file
# built_in
# error
# execution
# parsing
# signal
SRCS		=	minishell.c \
				minishell_utils.c \
\
				cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				export_utils.c \
				pwd.c \
				unset.c \
\
				error_utils.c\
				error.c \
\
				ex_utils.c \
				exec_builtin.c \
				here_doc.c \
				io_redirection.c \
				list.c \
				list_utils.c \
				mini_parsing_heredoc.c \
				path.c \
				pipe.c \
				pipe_utils.c \
				random_heredoc_gen.c \
\
				convert_list_to_string.c \
				parsing.c \
				parsing_list.c \
				parsing_utils.c \
				quote_handler.c \
				token.c \
				var_handler.c \
				var_utils.c \
\
				signal_handler.c \

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
	@$(CC) $(CFLAGS) $(OBJS) $(LDIR)$(LIBFT) uwu/C_tool.a -l readline -l ncurses \
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

leak: all
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --track-origins=yes --suppressions=$(PWD)/supp.txt ./minishell
