/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:02 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:43:04 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	word_count(char *s)
{
	int		i;
	int		count;
	char	q;

	i = 0;
	count = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			q = s[i++];
			while (s[i] && s[i] != q)
				i++;
			count++;
		}
		else if ((s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == 0))
			|| (ft_isalnum(s[i]) && (ft_cisredir(s[i + 1]) || s[i + 1] == '|'))
			|| (ft_isalnum(s[i + 1]) && (ft_cisredir(s[i]) || s[i] == '|')))
			count++;
		i++;
	}
	return (count);
}

void	change_token(t_lexer *lexer, t_token *token)
{
	if (lexer->c == lexer->s[lexer->i + 1])
	{
		if (lexer->c == '>')
			token->e_type = dredir_r;
		else
			token->e_type = dredir_l;
	}
	else
	{
		if (lexer->c == '>')
			token->e_type = redir_r;
		else
			token->e_type = redir_l;
	}
}

t_token	*init_token(int type, char *val)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->e_type = type;
	token->val = val;
	return (token);
}

t_toktab	init_token_tab(char	*s)
{
	t_toktab	tab;
	t_lexer		lexer;
	int			len;
	int			i;

	len = word_count(s);
	tab.tok = malloc(sizeof(t_token *) * len);
	tab.len = len;
	init_lexer(&lexer, s);
	i = 0;
	while (i < len)
	{
		tab.tok[i] = get_next_token(&lexer);
		if (i == 0 || (tab.tok[i - 1]->e_type == pip
				&& tab.tok[i]->e_type != pip))
			tab.tok[i]->e_type = cmd;
		if (tab.tok[i]->e_type == cmd && ft_strchr(tab.tok[i]->val, '$'))
			tab.tok[i]->e_type = dol_cmd;
		if (i > 0 && tab.tok[i]->val[0] == '-'
			&& tab.tok[i - 1]->e_type == cmd)
			tab.tok[i]->e_type = option;
		i++;
	}
	return (tab);
}

void	free_toktab(t_toktab tab)
{
	int	i;
	int	null;

	i = 0;
	null = 1;
	while (i < tab.len)
	{
		free(tab.tok[i]->val);
		free(tab.tok[i]);
		i++;
	}
	free(tab.tok);
}
