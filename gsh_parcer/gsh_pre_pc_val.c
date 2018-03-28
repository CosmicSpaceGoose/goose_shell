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

#include "libftprintf.h"

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
	if (*line)
		return (-1);
	return (flg);
}

static int	gsh_pc_val_wrds(char *line, int flg)
{
	while (*line && (*line == 32 || *line == 9))
		(line)++;
	if (!*line && flg == 1)
		return (-1);
	while (*line && *line != '|' && *line != ';')
	{
		if (*line == 60 || *line == 62)
		{
			line++;
			if ((*line == 60 || *line == 62) && (line++))
				if (*line == 60 && *(line + 1) == 38)
					return (-1);
			*line == 38 ? line++ : 0;
			while (*line == 32 || *line == 9)
				line++;
			if (*line == 38 || !*line || *line == 59 || *line == '|')
				return (-1);
		}
		else
			*line == '\\' ? line++ : 0;
		line++;
	}
	flg = 0;
	return (flg);
}

int			gsh_pc_validate(char **in)
{
	int flg;

	flg = -1;
	while (*in)
	{
		if (**in && (**in == ';' || **in == '|'))
		{
			if ((flg = gsh_pc_val_redir(*in, flg)) < 0)
				return (1);
		}
		else
		{
			if ((flg = gsh_pc_val_wrds(*in, flg)) < 0)
				return (1);
		}
		in++;
	}
	if (flg == 1)
		return (1);
	return (0);
}
