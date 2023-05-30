#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_strsearch(char *string, char character);

size_t	ft_strlen(const char *s);
size_t	ft_strlen_double(char **s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *old, size_t size, size_t len, size_t new_len);
void	*ft_xfree(void	*pointer);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);

/* *********************************BONUS************************************ */

int		ft_lstsize(t_list *lst);

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ********************************FT_PRINTF********************************* */

int		ft_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);
int		ft_printchar(int c, int fd);
int		ft_printstr(char *str, int fd);
int		ft_printnbr(int nbr, int fd);
int		ft_printunnbr(unsigned int nbr, int fd);
int		ft_printhex(unsigned int nbr, const char format, int fd);
int		ft_printptr(uintptr_t ptr, int fd);

/* ******************************GET_NEXT_LINE******************************* */

char	*get_next_line(int fd);
char	*ft_fstrjoin(char *s1, char *s2);

/* *********************************OTHER************************************ */

int		ft_intlen(long int n, int base);
int		ft_isfile(char *file);
int		ft_strcmp(char *s1, char *s2);

long	ft_atol(const char *str);

void	*ft_fcalloc(void *ptr, size_t count, size_t size);

char	**ft_split_char(const char *lines);
char	*ft_rstrjoin(char const *s1, char const *s2);
char	*ft_frstrjoin(char *s1, char *s2);
char	*ft_convertbase(char *num, int initbase, int finalbase);
char	**ft_free_null(char **array);

#endif
