/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_pre_pc_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:29:56 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/14 14:29:58 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		PRE_PARCER_2
*/

static int	gsh_pc_val_redir(char *line, int flg)
{
	int c;

	c = *line;
	if (!(flg == -1 && c == ';') && (flg == 1 || (flg == 2 && c != ';')))
		return (-1);
	if (c != ';')
		flg = 1;
	else
		flg = 2;
	line++;
	if (*line == c)
		line++;
	else if (*line)
		return (-1);
	return (flg);
}

static int	gsh_pc_val_wrds(char *line, int flg)
{
	while (*line && (*line == ' ' || *line == '\t'))
		(line)++;
	if (!*line && flg == 1)
		return (-1);
	while (*line && *line != '|' && *line != ';' && *line != '&')
	{
		if (*line == '<' || *line == '>')
		{
			line++;
			if ((*line == '<' || *line == '>') && (line++))
				if (*line == '<' && *(line + 1) == '&')
					return (-1);
			*line == '&' ? line++ : 0;
			while (*line == ' ' || *line == '\t')
				line++;
			if (!*line || *line == '&' || *line == ';' || *line == '|')
				return (-1);
		}
		else
			*line == '\\' ? line++ : 0;
		line++;
	}
	flg = 0;
	return (flg);
}

static int	gsh_pc_word_token(char *str, int c)
{
	int rat;

	rat = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (!c)
				c = *str;
			else if (c == *str)
				c = 0;
		}
		else if (*str == '\\')
			str++;
		else if (!c && (*str == '<' || *str == '>'))
		{
			if (*str == '<')
				rat |= 1;
			else
				rat |= 2;
		}
		str++;
	}
	return (rat);
}

static int	gsh_pc_delim_token(char *str)
{
	int c;

	c = 0;
	if (*str == ';')
		c = 'e';
	else if (*str == '|')
	{
		if (*(str + 1) == '|')
			c = 'o';
		else
			c = 'p';
	}
	else if (*str == '&' && *(str + 1) == '&')
		c = 'a';
	return (c);
}

int			gsh_pc_validate(t_ok **in)
{
	int		flg;
	char	*str;

	flg = -1;
	while (*in)
	{
		str = (*in)->str;
		if (*str && (*str == ';' || *str == '|' || *str == '&'))
		{
			if ((flg = gsh_pc_val_redir(str, flg)) < 0)
				return (1);
			(*in)->tok = gsh_pc_delim_token(str);
		}
		else
		{
			if ((flg = gsh_pc_val_wrds(str, flg)) < 0)
				return (1);
			(*in)->tok = gsh_pc_word_token(str, 0);
		}
		in++;
	}
	if (flg == 1)
		return (1);
	return (0);
}
