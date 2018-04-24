/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:32:53 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/15 16:32:55 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		YEAP, ITS A MAIN  ###  GOOSE_SHELL V2.17.04.18
*/

/*
**		pps[0] - total number of pipes (redir include),
**		pps[1] - position in pipe's chain
*/

int		gsh_check_pipeline(int num, int ttl)
{
	if (num && !ttl)
		return (END_PPL);
	else if (num != ttl)
		return (MIDDLE_PPL);
	else if (num && num == ttl)
		return (BEGIN_PPL);
	return (0);
}

static void	gsh_count_pipes(t_tok **lines, int *pps)
{
	int		ttl;
	int		tok;

	ttl = 0;
	tok = (*lines)->tok;
	while (*lines)
	{
		if ((*lines)->tok == 'p')
			ttl++;
		else if ((*lines)->tok == 'e')
			break ;
		lines++;
	}
	if (!pps[0] && ttl)
		pps[0] = ttl;
	pps[1] = gsh_check_pipeline(pps[0], ttl);
}

/*
**		MAKE PIPES
*/

void	close_all_pipes(int *cp, int **fds, int *pps)
{
	int i;

	i = pps[0] * 2;
	while (i > 0)
	{
		i--;
		close(cp[i]);
	}
	free(cp);
	*fds = NULL;
	pps[0] = 0;
	pps[1] = 0;
}

void	open_all_pipes(int **fds, int **cp, int i)
{
	int z;

	z = 0;
	*fds = (int *)malloc(sizeof(int) * i);
	*cp = *fds;
	while (z < i)
	{
		pipe(*fds + z);
		z += 2;
	}
}

void		gsh_free_tok(t_tok **tok)
{
	t_tok **cp;

	cp = tok;
	while (*tok)
	{
		free((*tok)->str);
		free(*tok);
		*tok = NULL;
		tok++;
	}
	free(cp);
	tok = NULL;
}

static void	gsh_cycle(t_tok **lines)
{
	int		i;
	int		pps[3];
	int		*cp;
	int		*fds;

	if (gsh_pc_validate(lines))
		ft_putendl_fd("|< parcing/syntax error", 2);
	else
	{
		i = 0;
		pps[0] = 0;
		pps[1] = 0;
		cp = NULL;
		fds = NULL;
		while (lines[i])
		{
			if ((lines[i])->tok == 'e' || (lines[i])->tok == 'p')
			{
				i++;
				continue ;
			}
			ft_dprintf(2, "{%s}\n", (lines[i])->str);				//<<----☢
			gsh_count_pipes(lines + i, pps);
			fds == NULL && pps[0] ? open_all_pipes(&fds, &cp, pps[0] * 2): 0;
			if (pps[1] > 1)
				fds += 2;
			if (gsh_seek((lines[i])->str, pps, fds) > 255)
				break ;
			i++;
			if (fds && (!lines[i] || (lines[i])->str[0] == ';'))
				close_all_pipes(cp, &fds, pps);
		}
	}
	gsh_free_tok(lines);
}

int			main(void)
{
	char	*line;
	char	*ptr;
	int		rat;

	if (!isatty(0))
		return (0);
	gsh_init(0);
	rat = 0;
	// gsh_write_head();
	while (gsh_reader(&line, gsh_prompt(1)))
	{
		ft_dprintf(2, "[%s]\n", line);								//<<----☢
		while ((ptr = ft_strrchr(line, 92)) && *(ptr + 1) == '\0'
			&& *(ptr - 1) != 92)
			gsh_readmoar_atzero(&line);
		line[0] ? gsh_cycle(gsh_pc_lines(line)) : 0;
		free(line);
		if ((rat = ft_atoi(gsh_get_env("?"))) > 255)
			break ;
	}
	// exit_draw();
	ft_dprintf(1, "exit:%d", rat);
	gsh_r_history_bucket(-1, NULL);
	gsh_bucket(3, 0);
	system("leaks 21sh | tail -n 4");
	return (rat);
}