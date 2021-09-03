/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 21:25:20 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/12 21:25:23 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	empty(char *s)
{
	char	c;

	if (s[0] && s[0] && (s[0] == '\'' || s[0] == '\"'))
	{
		c = s[0];
		if (s[1] && s[1] == c)
		{
			ft_putstr("bash: : command not found\n");
			g_sig.ret = 1;
			return (1);
		}
	}
	return (0);
}

int	get_quote(char *s)
{
	int		i;
	int		quote;
	char	type;

	if (!s)
		return (0);
	i = 0;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !quote)
		{
			type = s[i];
			quote = 1;
		}
		else if (quote && s[i] == type)
			quote = 0;
		i++;
	}
	if (quote)
		ft_putendl("Unclosed quotes, please try again without it");
	return (quote);
}
