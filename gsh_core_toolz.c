/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_core_toolz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:26:49 by dlinkin           #+#    #+#             */
/*   Updated: 2018/04/25 18:26:51 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

int		gsh_heredoc(char *str)
{
	int		fd[2];
	char	*buf;

	pipe(fd);
	buf = NULL;
	while (gsh_reader(&buf, write(0, "heredoc> ", 9)))
	{
		if (!ft_strcmp(str, buf))
			break ;
		ft_putstr_fd(buf, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(buf);
		buf = NULL;
		gsh_r_history_bucket(1, NULL);
	}
	free(buf);
	close(fd[1]);
	return (fd[0]);
}

/*
**		pps[0] - total number of pipes,
**		pps[1] - position in pipe's chain,
**		pps[2] - redirection true/false.
*/

static void	gsh_count_pipes(t_orba **z, int *pps)
{
	int		ttl;

	ttl = 0;
	while (*z)
	{
		if ((*z)->red)
			pps[2] |= 1;
		if ((*z)->tok == 'p')
			ttl++;
		else if ((*z)->tok == 'e')
			break ;
		z++;
	}
	if (!pps[0] && ttl)
		pps[0] = ttl;
	if (pps[0] && !ttl)
		pps[1] = END_PPL;
	else if (pps[0] != ttl)
		pps[1] = MIDDLE_PPL;
	else if (pps[0] && pps[0] == ttl)
		pps[1] = BEGIN_PPL;
	else
		pps[1] = 0;
}

/*
**		MAKE PIPES
*/

void		open_close_pipes(int **fds, int **cp, int i, int mod)
{
	int k;

	if (!mod)
	{	
		while (i > 0)
		{
			i--;
			close((*cp)[i]);
		}
		*fds = NULL;
		free(*cp);
	}
	else
	{
		k = 0;
		*fds = (int *)malloc(sizeof(int) * i);
		*cp = *fds;
		while (k < i)
		{
			pipe(*fds + k);
			k += 2;
		}
	}
}

void		open_files(t_orba **z)
{
	int		k;

	while (*z && (*z)->tok != 'e')
	{
		if ((*z)->red)
		{
			k = 0;
			while ((*z)->red[k])
			{
				if (((*z)->red[k])->io != 'I' && ((*z)->red[k])->ptr)
					((*z)->red[k])->fd = open(((*z)->red[k])->ptr,
						((*z)->red[k])->flgs, 0666);
				else if (((*z)->red[k])->io == 'I')
					((*z)->red[k])->fd = gsh_heredoc(((*z)->red[k])->ptr);
				k++;
			}
		}
		z++;
	}
}

void		close_files(t_orba *z, int *pps)
{
	int k;

	if (z->red)
	{
		k = 0;
		while (z->red[k])
		{
			if ((z->red[k])->fd != -1)
				close((z->red[k])->fd);
			k++;
		}
		pps[2] = 0;
	}
}

void		gsh_cycle(t_orba **z, int *pps, int *fds, int *cp)
{
	while (*z)
	{
		if ((*z)->tok == 'e' || (*z)->tok == 'p')
		{
			z++;
			continue ;
		}
		gsh_count_pipes(z, pps);
		if (fds == NULL && pps[0])
			open_close_pipes(&fds, &cp, pps[0] * 2, 1);
		pps[1] > 1 ? fds += 2 : 0;
		if (pps[2] && pps[1] < 2)
			open_files(z);
		if (gsh_seek(*z, pps, fds) > 255)
			break ;
		pps[2] ? close_files(*z, pps) : 0;
		z++;
		if (fds && (!*z || (*z)->tok == 'e'))
		{
			open_close_pipes(&fds, &cp, pps[0] * 2, 0);
			pps[0] = 0;
			pps[1] = 0;
			pps[2] = 0;
		}
	}
}
