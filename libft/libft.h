/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 06:08:35 by srheede           #+#    #+#             */
/*   Updated: 2018/08/28 09:49:05 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <libc.h>

# define BUFF_SIZE 1
# define MAX_SIZE_FD 100

typedef struct		s_list
{
	int				data;
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_gnl
{
	char			**fd;
	char			***arr;
}					t_gnl;

void				ft_arrdel(char **arr);
int					*ft_arrcpy(int *dst, const int *src, size_t len);
int					*ft_arrdup(const int *src, size_t len);
t_list				*ft_arrtolst(char **arr);
size_t				ft_arrlen(char **arr);
int					ft_atoi(const char *str);
int					ft_abs(int n);
void				ft_bzero(void *s, size_t n);
void				ft_div_mod(int a, int b, int *div, int *mod);
int					ft_factorial(int i);
int					ft_fibonacci(int i);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isbracket(int c);
int					ft_isbracket_closed(int c);
int					ft_isbracket_open(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
char				*ft_itoa(int n);
size_t				ft_line_count(char const *s);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
int					ft_lstsize(t_list *list);
char				**ft_lsttoarr(t_list *list);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
int					ft_next_prime(int nb);
int					ft_op(int i, char c, int j);
int					ft_powerof(int nb, int power);
void				ft_putarr_fd(char **arr, int fd);
void				ft_putarr_nl_fd(char **arr, int fd);
void				ft_putarr_nl(char **arr);
void				ft_putarr_sp(char **arr);
void				ft_putarri_nl(int *arr);
void				ft_putarr(char **arr);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putstr(const char *str);
void				*ft_revmemcpy(void *dst, const void *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *src);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen_c(const char *s, char c);
size_t				ft_strlen(const char *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(char *src, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplit_lines(char const *s);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_swap(int *a, int *b);
int					ft_sqrt(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					get_next_line(const int fd, char **line);
void				quicksort(int *arr, int first, int last);
t_list				*sort_list(t_list *lst, int (*cmp)(int, int));

#endif
