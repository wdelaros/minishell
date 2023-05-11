#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

NAME			=	libft.a

# Style
BOLD			=	\033[1m
ITALIC			=	\033[3m
UNDERLINE		=	\033[4m

# Color text
RESET			=	\033[0m
BLACK			=	\033[30m
RED				=	\033[31m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
PURPLE			=	\033[35m
CYAN			=	\033[36m
WHITE			=	\033[37m
DEFAULT			=	\033[39m
ERASE_LINE		=	\033[2K\r

# Compiler and flags
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -rf

# Sources are all .c files
#int
#list
#mem
#str
#write
SRCS_LST		=	ft_atoi.c\
					ft_intlen.c\
					ft_isalnum.c\
					ft_isalpha.c\
					ft_isascii.c\
					ft_isdigit.c\
					ft_itoa.c\
					ft_atol.c\
\
					ft_lstadd_back.c\
					ft_lstadd_front.c\
					ft_lstclear.c\
					ft_lstdelone.c\
					ft_lstiter.c\
					ft_lstlast.c\
					ft_lstmap.c\
					ft_lstnew.c\
					ft_lstsize.c\
\
					ft_calloc.c\
					ft_fcalloc.c\
					ft_memchr.c\
					ft_memcmp.c\
					ft_memcpy.c\
					ft_memmove.c\
					ft_memset.c\
					ft_realloc.c\
					ft_xfree.c\
\
					ft_bzero.c\
					ft_convertbase.c\
					ft_fstrjoin.c\
					ft_isfile.c\
					ft_isprint.c\
					ft_split.c\
					ft_strchr.c\
					ft_strdup.c\
					ft_striteri.c\
					ft_strjoin.c\
					ft_strlcat.c\
					ft_strlcpy.c\
					ft_strlen.c\
					ft_strmapi.c\
					ft_strncmp.c\
					ft_strnstr.c\
					ft_strrchr.c\
					ft_strtrim.c\
					ft_substr.c\
					ft_tolower.c\
					ft_toupper.c\
					get_next_line.c\
\
					ft_printf.c\
					ft_printf_utils.c\
					ft_printhex.c\
					ft_printptr.c\
					ft_putchar_fd.c\
					ft_putendl_fd.c\
					ft_putnbr_fd.c\
					ft_putstr_fd.c\

OBJS_DIR		=	obj/
OBJS_LST		=	$(patsubst %.c, %.o, $(SRCS_LST))
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

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
$(OBJS_DIR)%.o: src/*/%.c
	@printf "$(ERASE_LINE)⚙️ $(PURPLE)Compiling $(DEFAULT)⚙️$(YELLOW) $(notdir $<)\
	$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# create objects directory
dir:
	@mkdir -p $(OBJS_DIR)

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