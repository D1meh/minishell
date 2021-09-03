/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:05 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:07 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*quote_token(t_lexer *lexer)
{
	t_token	*token;
	char	*tmp;
	char	*s;
	char	q;

	token = malloc(sizeof(t_token));
	token->e_type = d_quote;
	if (lexer->c == '\'')
		token->e_type = s_quote;
	q = lexer->c;
	lexer_advance(lexer);
	s = malloc(sizeof(char));
	s[0] = 0;
	while (lexer->c != q && lexer->c)
	{
		tmp = char_toa(lexer->c);
		s = ft_realloc(s, ft_strlen(s) + 1);
		ft_strcat(s, tmp);
		free(tmp);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	token->val = s;
	return (token);
}

t_token	*redir_token(t_lexer *lexer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (lexer->s[lexer->i] == lexer->s[lexer->i + 1])
	{
		token->val = malloc(sizeof(char) * 3);
		token->val[0] = lexer->s[lexer->i];
		token->val[1] = token->val[0];
		token->val[2] = 0;
		token->e_type = dredir_r;
		if (lexer->s[lexer->i] == '<')
			token->e_type = dredir_l;
		lexer_advance(lexer);
	}
	else
	{
		token->val = malloc(sizeof(char) * 2);
		token->val[0] = lexer->s[lexer->i];
		token->val[1] = 0;
		token->e_type = redir_r;
		if (lexer->s[lexer->i] == '<')
			token->e_type = redir_l;
	}
	lexer_advance(lexer);
	return (token);
}

t_token	*pipe_token(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (init_token(pip, char_toa('|')));
}

t_token	*dollar_token(t_lexer *lexer)
{
	char	*s;
	char	*tmp;

	s = malloc(sizeof(char));
	s[0] = 0;
	while (lexer->c && lexer->c != ' ')
	{
		tmp = char_toa(lexer->c);
		s = ft_realloc(s, ft_strlen(s) + 1);
		ft_strcat(s, tmp);
		free(tmp);
		lexer_advance(lexer);
	}
	return (init_token(dollar, s));
}

t_token	*string_token(t_lexer *lexer)
{
	t_token	*token;
	char	*s;
	char	*tmp;

	token = malloc(sizeof(t_token));
	token->e_type = id;
	s = ft_strdup("");
	while (lexer->c && lexer->c != ' ' && !ft_cisredir(lexer->c)
		&& lexer->c != '|')
	{
		if (lexer->c == '=')
			token->e_type = equal;
		if (lexer->c == '$' && token->e_type != equal)
			token->e_type = dollar;
		if (token->e_type == id && (lexer->c == '>' || lexer->c == '<'))
			change_token(lexer, token);
		tmp = char_toa(lexer->c);
		s = ft_realloc(s, ft_strlen(s) + 1);
		ft_strcat(s, tmp);
		free(tmp);
		lexer_advance(lexer);
	}
	token->val = s;
	return (token);
}
