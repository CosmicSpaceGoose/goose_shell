/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_some_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:43:35 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/22 16:43:36 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		CONVERT char *redirection INTO STRUCT t_redir
*/

static int	gsh_red_get_word(char *red, t_redir *sum)
{
	struct stat bu;

	if (sum->amp == 2 && (ft_isnumber(red) || (*red == '-' && !*(red + 1))))
	{
		if (*red != '-')
			if (fstat((sum->new = ft_atoi(red)), &bu))
			{
				ft_dprintf(2, "|< bad file descriptor: %d\n", sum->new);
				return (1);
			}
	}
	else
	{
		sum->ptr = red;
		if (sum->io == 'i' && access(red, F_OK))
			ft_dprintf(2, "|< no such file or directory: %s\n", red);
		else if (((sum->io == 'o' || sum->io == 'O') && !access(red, F_OK)
			&& access(red, W_OK)) || (sum->io == 'i' && access(red, R_OK)))
			ft_dprintf(2, "|< permission denied: %s\n", red);
		else
			return (0);
		return (1);
	}
	return (0);
}

static void	gsh_red_io_flags(char **red, t_redir *sum)
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

static int	gsh_red_converter(char *red, t_redir *sum)
{
	sum->old = -1;
	sum->new = -1;
	sum->amp = -1;
	sum->ptr = NULL;
	if (*red > 47 && *red < 58 && (red++))
		sum->old = (*(red - 1) - 48);
	if (*red == 38 && (red++))
		sum->amp = 1;
	gsh_red_io_flags(&red, sum);
	if (*red == 38 && (red++))
		sum->amp = 2;
	return (gsh_red_get_word(red, sum));
}

int			make_sum_redir(char **red)
{
	t_redir	sum;
	int		new;

	while (*red)
	{
		ft_putendl_fd("HALLO", 2);
		if (gsh_red_converter(*red, &sum))
			return (1);
////////////////													//<<----☢
		ft_dprintf(2, "%c:%d:%d:%d:%d %s\n", sum.io, sum.old, sum.new,
			sum.amp, sum.flgs, sum.ptr);
////////////////
		if (sum.io != 'I' && sum.ptr)
			new = open(sum.ptr, sum.flgs, 0666);
		else if (!sum.ptr)
			new = sum.new;
		if (new != -1)
			dup2(new, sum.old);
		else
			close(sum.old);
		red++;
	}
	return (0);
}
