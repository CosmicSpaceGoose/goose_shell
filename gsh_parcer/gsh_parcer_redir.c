/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_parcer_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:50:56 by dlinkin           #+#    #+#             */
/*   Updated: 2018/04/24 14:50:57 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		CONVERT char *redirection INTO STRUCT t_redir
*/

static void		gsh_red_io_flags(char **red, t_redir *sum)
{
	if (**red == '<' && ((*red)++))
	{
		sum->old == -1 ? sum->old = 0 : 0;
		if (**red == '<' && ((*red)++))
			sum->io = 'I';
		else
			sum->io = 'i';
		sum->flgs = O_RDONLY;
	}
	else if (**red == '>' && ((*red)++))
	{
		sum->old == -1 ? sum->old = 1 : 0;
		if (**red == '>' && ((*red)++))
		{
			sum->io = 'O';
			sum->flgs = O_WRONLY | O_CREAT | O_APPEND;
		}
		else
		{
			sum->io = 'o';
			sum->flgs = O_WRONLY | O_CREAT | O_TRUNC;
		}
	}
}

static t_redir	*gsh_red_converter(char *red)
{
	t_redir	*sum;

	sum = (t_redir *)malloc(sizeof(t_redir));
	sum->old = -1;
	sum->new = -1;
	sum->amp = -1;
	sum->ptr = NULL;
	sum->fd = -1;
	if (*red > 47 && *red < 58 && (red++))
		sum->old = (*(red - 1) - 48);
	if (*red == 38 && (red++))
		sum->amp = 1;
	gsh_red_io_flags(&red, sum);
	if (*red == 38 && (red++))
		sum->amp = 2;
	if (sum->amp == 2 && (ft_isnumber(red) || (*red == '-' && !*(red + 1))))
	{
		if (*red != '-')
			sum->new = ft_atoi(red);
	}
	else
		sum->ptr = ft_strdup(red);
	return (sum);
}

t_redir			**gsh_parce_redir(char **red)
{
	t_redir	**or;
	int		i;

	or = NULL;
	if (red)
	{
		i = 0;
		while (red[i])
			i++;
		or = (t_redir **)malloc(sizeof(t_redir *) * (i + 1));
		or[i] = NULL;
		while (i)
		{
			i--;
			or[i] = gsh_red_converter(red[i]);
		}
	}
	return (or);
}
