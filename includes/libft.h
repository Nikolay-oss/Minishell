/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:01:35 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 23:38:34 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
char				**ft_split(char const *s, char c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c,
						size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_substr(char const *s, unsigned int start,
						size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);

typedef struct s_node
{
	struct s_node	*next;
	void			*content;
}					t_node;

typedef struct s_list
{
	t_node			*head;
	t_node			*tail;
	size_t			size;
}					t_list;

t_list				*ft_create_lst(void);
t_node				*ft_create_node(void *data);
void				ft_push_front(t_list *lst, void *data);
void				ft_push_back(t_list *lst, void *data);
void				ft_lst_clear(t_list *lst, void (*del)(void*));

#endif
