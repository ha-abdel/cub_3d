/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:41:21 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/06/24 15:52:10 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_allocs
{
	void			*ptr;
	struct s_allocs	*next;
}					t_allocs;

// #include "minishell.h"

void				*ft_malloc(size_t size, int flag);
void				ft_free(t_allocs **lst);

int					ft_strlen(char *s);
int					ft_isdigit(int c);

int					ft_isalpha(int c);

int					ft_isalnum(int c);

int					ft_isascii(int c);

int					ft_isprint(int c);

void				*ft_memset(void *b, int c, int len);

void				ft_bzero(void *s, int n);

void				*ft_memcpy(void *dst, void *src, int n);

void				*ft_memmove(void *dst, void *src, int len);

int					ft_strlcpy(char *dst, char *src, int dstsize);

int					ft_strlcat(char *dst, char *src, int dstsize);

char				*ft_strtrim(char *s1, char *set);

int					ft_toupper(int c);

int					ft_tolower(int c);

char				*ft_strchr(char *s, int c);

char				*ft_strrchr(char *s, int c);

int					ft_strncmp(char *s1, char *s2, int n);

void				*ft_memchr(void *s, int c, int n);

int					ft_memcmp(void *s1, void *s2, int n);

char				*ft_strnstr(char *haystack, char *needle, int len);

int     ft_atoi(const char *str, int *flag);

void				*ft_calloc(int count, int size);

char				*ft_strdup(char *s1);

char				*ft_substr(char *s, int start, int len);

char				*ft_strtrim(char *s1, char *set);

char				*ft_strjoin(char *s1, char *s2);

char				**ft_split(char *s, char *sep);

char				*ft_itoa(int n);

char				*ft_strmapi(char *s, char (*f)(unsigned int, char));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);

void				ft_lstadd_front(t_list **lst, t_list *new);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
