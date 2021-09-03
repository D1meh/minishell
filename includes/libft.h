/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:37:28 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:37:30 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}	t_var;

void	ft_freetab(char **tab);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl(char *s);
char	*ft_itoa(int n);
char	*ft_strchr(char *s, char c);
char	*ft_strstr(char *s, char *l);
char	*ft_strcat(char *dst, char *src);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_no_free(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*ft_realloc(char *s, int size);
char	**ft_split(char *s, char c);
int		ft_isprint(int c);
int		ft_isalnum(char c);
int		ft_isredir(char *s);
int		ft_cisredir(char c);
int		ft_isspace(char *s);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_gnl(char **line, int fd);

t_var	**ft_varreplace(t_var **v, char *name, char *val);
t_var	*ft_varnew(char *name, char *value);
t_var	*ft_varlast(t_var *var);
char	*ft_varexist(t_var *v, char *name);
void	ft_varadd_back(t_var **v, t_var *new);
void	ft_varadd_front(t_var **v, t_var *new);
void	ft_vardel(t_var **var, char *name);
void	ft_varclear(t_var **v);
int		ft_varsize(t_var *var);

#endif
