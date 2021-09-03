/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_smth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:39:12 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:39:13 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalnum(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isprint(int c)
{
	if (c > 32 && c < 127)
		return (1);
	return (0);
}

int	ft_isredir(char *s)
{
	if (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0
		|| ft_strcmp(s, "<<") == 0 || ft_strcmp(s, ">>") == 0)
		return (1);
	return (0);
}

int	ft_cisredir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_isspace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
