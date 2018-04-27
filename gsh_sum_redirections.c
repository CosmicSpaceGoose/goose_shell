/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_sum_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:46:43 by dlinkin           #+#    #+#             */
/*   Updated: 2018/04/26 14:46:45 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void	gsh_sum(t_redir *red)
{
	if (!red->ptr && red->new != -1)
		dup2(red->new, red->old);
	else if (!red->ptr && red->new == -1)
		close(red->old);
	else
	{
		dup2(red->fd, red->old);
		if (red->old == 1 && red->amp)
			dup2(red->fd, 2);
	}
}

int			gsh_make_sum_redir(t_redir **red)
{
	struct stat bu;

	while (*red)
	{
		if ((*red)->ptr && (*red)->fd == -1)
		{
			if ((*red)->io == 'i' && access((*red)->ptr, F_OK))
				ft_dprintf(2, "|< no such file/directory: %s\n", (*red)->ptr);
			else if (((*red)->io == 'i' && access((*red)->ptr, R_OK)) ||
	(((*red)->io == 'o' || (*red)->io == 'O') && access((*red)->ptr, W_OK)))
				ft_dprintf(2, "|< permission denied: %s\n", (*red)->ptr);
			return (1);
		}
		else if (!(*red)->ptr && fstat((*red)->new, &bu))
		{
			ft_dprintf(2, "|< bad file descriptor: %d\n", (*red)->ptr);
			return (1);
		}
		gsh_sum(*red);
		red++;
	}
	return (0);
}
