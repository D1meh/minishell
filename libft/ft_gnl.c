/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:39:07 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:39:08 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	bufL(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	new_line(char **s, int fd)
{
	int		n;
	char	*tmp;
	char	buf[33];

	n = read(fd, buf, 32);
	if (n < 1)
		return (n);
	buf[n] = 0;
	tmp = ft_strjoin_no_free(*s, buf);
	free(*s);
	*s = tmp;
	return (n);
}

static void	final_free(void **s)
{
	free(*s);
	*s = NULL;
}

int	ft_gnl(char **line, int fd)
{
	static char	*s = NULL;
	char		*tmp;
	int			n;

	if (!line || read(fd, s, 0) < 0)
		return (-1);
	if (s == NULL)
		s = ft_strdup("");
	n = 1;
	while (n > 0 && !ft_strchr(s, '\n'))
		n = new_line(&s, fd);
	if (n < 0)
		return (-1);
	else if (n == 0)
		*line = ft_strdup(s);
	else
		*line = ft_substr(s, 0, bufL(s));
	tmp = ft_substr(s, bufL(s) + 1, ft_strlen(s) - bufL(s));
	free(s);
	s = tmp;
	if (n > 0)
		return (1);
	final_free((void **)&s);
	return (0);
}
