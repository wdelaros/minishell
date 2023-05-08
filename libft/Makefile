#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

NAME		=	libft.a

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
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf

# Sources are all .c files
SRCS		=	int/ft_atoi.c\
				int/ft_intlen.c\
				int/ft_isalnum.c\
				int/ft_isalpha.c\
				int/ft_isascii.c\
				int/ft_isdigit.c\
				int/ft_itoa.c\
\
				list/ft_lstadd_back.c\
				list/ft_lstadd_front.c\
				list/ft_lstclear.c\
				list/ft_lstdelone.c\
				list/ft_lstiter.c\
				list/ft_lstlast.c\
				list/ft_lstmap.c\
				list/ft_lstnew.c\
				list/ft_lstsize.c\
\
				mem/ft_calloc.c\
				mem/ft_fcalloc.c\
				mem/ft_memchr.c\
				mem/ft_memcmp.c\
				mem/ft_memcpy.c\
				mem/ft_memmove.c\
				mem/ft_memset.c\
\
				str/ft_bzero.c\
				str/ft_convertbase.c\
				str/ft_fstrjoin.c\
				str/ft_isfile.c\
				str/ft_isprint.c\
				str/ft_split.c\
				str/ft_strchr.c\
				str/ft_strdup.c\
				str/ft_striteri.c\
				str/ft_strjoin.c\
				str/ft_strlcat.c\
				str/ft_strlcpy.c\
				str/ft_strlen.c\
				str/ft_strmapi.c\
				str/ft_strncmp.c\
				str/ft_strnstr.c\
				str/ft_strrchr.c\
				str/ft_strtrim.c\
				str/ft_substr.c\
				str/ft_tolower.c\
				str/ft_toupper.c\
				str/get_next_line.c\
\
				write/ft_printf.c\
				write/ft_printf_utils.c\
				write/ft_printhex.c\
				write/ft_printptr.c\
				write/ft_putchar_fd.c\
				write/ft_putendl_fd.c\
				write/ft_putnbr_fd.c\
				write/ft_putstr_fd.c\

OBJS_DIR	=	obj/
OBJS_LST	=	$(patsubst %.c, %.o, $(SRCS))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: dir $(NAME)

# Generates output file
$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(ERASE_LINE)$(GREEN)✔️ $(ITALIC)Libft successfully created.$(RESET)\
	$(GREEN) ✔️$(RESET)"

# Compiles sources into objects
$(OBJS_DIR)%.o: %.c
	@printf "$(ERASE_LINE)⚙️ $(PURPLE)Compiling $(DEFAULT)⚙️$(YELLOW) $(notdir $<)\
	$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# create objects directory
dir:
	@mkdir -p $(OBJS_DIR)/int/
	@mkdir -p $(OBJS_DIR)/list/
	@mkdir -p $(OBJS_DIR)/mem/
	@mkdir -p $(OBJS_DIR)/str/
	@mkdir -p $(OBJS_DIR)/write/

# Removes objects
clean:
	@printf "💣 $(RED)Removing libft objects...$(RESET) 💥\n"
	@$(RM) $(OBJS_DIR)

# Removes objects and executables
fclean: clean
	@printf "💣 $(RED)Removing libft executable$(RESET) 💥\n"
	@$(RM) $(NAME)

# Removes objects and executables and remakes
re: fclean all