/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:48 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:49 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_lexer(t_lexer *lexer, char *s)
{
	lexer->s = s;
	lexer->i = 0;
	lexer->c = s[lexer->i];
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->s))
	{
		lexer->i++;
		lexer->c = lexer->s[lexer->i];
	}
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->s))
	{
		while (lexer->c == ' ' || lexer->c == '\n')
			lexer_advance(lexer);
		if (lexer->c == '\"' || lexer->c == '\'')
			return (quote_token(lexer));
		else if (lexer->c == '<' || lexer->c == '>')
			return (redir_token(lexer));
		else if (lexer->c == '|')
			return (pipe_token(lexer));
		else if (lexer->c == '$')
			return (dollar_token(lexer));
		else if (ft_isprint(lexer->c))
			return (string_token(lexer));
	}
	return (NULL);
}
