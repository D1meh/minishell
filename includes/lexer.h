/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:37:25 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:37:26 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	enum {
		id,
		cmd,
		option,
		s_quote,
		d_quote,
		pip,
		equal,
		dollar,
		dol_cmd,
		redir_l,
		redir_r,
		dredir_l,
		dredir_r,
	}		e_type;
	char	*val;
}	t_token;

typedef struct s_toktab
{
	struct s_token	**tok;
	int				len;
	int				curr;
	char			*temp[50000];
}	t_toktab;

typedef struct s_lexer
{
	int		i;
	char	c;
	char	*s;
}	t_lexer;

void		init_lexer(t_lexer *lexer, char *s);
void		lexer_advance(t_lexer *lexer);
void		free_toktab(t_toktab tab);
void		change_token(t_lexer *lexer, t_token *token);

t_token		*init_token(int type, char *val);
t_token		*get_next_token(t_lexer *lexer);
t_toktab	init_token_tab(char *s);

t_token		*quote_token(t_lexer *lexer);
t_token		*redir_token(t_lexer *lexer);
t_token		*pipe_token(t_lexer *lexer);
t_token		*dollar_token(t_lexer *lexer);
t_token		*string_token(t_lexer *lexer);

char		*char_toa(char c);

#endif
