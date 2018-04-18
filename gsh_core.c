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

int		gsh_check_pipeline(int num, int ttl, int tok)
{
	if (tok)
	{
		if (tok == 1)
		{
			if (ttl > 1)
				return (MIDDLE_PPL);
			return (END_PPL);
		}
		if (tok == 2)
		{
			if (num != ttl)
				return (MIDDLE_PPL);
			return (BEGIN_PPL);
		}
		return (MIDDLE_PPL);
	}
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
	char	*str;
	int		tok;

	ttl = 0;
	tok = (*lines)->tok;
	while (*lines)
	{
		str = (*lines)->str;
		if (*str == '|')
			ttl++;
		else if (*str == ';')
			break ;
		else
		{
			!ttl && ((*lines)->tok & 1) ? (ttl++) : 0;
			((*lines)->tok & 2) && (!*(lines + 1)
				|| (*(lines + 1))->tok != 'p') ? (ttl++) : 0;
		}
		lines++;
	}
	if (!pps[0] && ttl)
		pps[0] = ttl;
	pps[1] = gsh_check_pipeline(pps[0], ttl, tok);
	ft_dprintf(2, "TOTAL=%d ELEM=%d\t", pps[0], pps[1]);			//<<----☢
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
		// ft_dprintf(2, "%d-%p\n", i, &cp[i]);					//<<----☢
		close(cp[i]);
	}
	free(cp);
	gsh_std_save_restore(RESTORE);
	*fds = NULL;
	pps[0] = 0;
	pps[1] = 0;
}

void	open_all_pipes(int **fds, int **cp, int i)
{
	int z;

	z = 0;
	*fds = (int *)malloc(sizeof(int) * i);
	// ft_dprintf(2, "--->>>%d<<<---\n", i);					//<<----☢
	*cp = *fds;
	while (z < i)
	{
		pipe(*fds + z);
		// ft_dprintf(2, "%p\n%p\n", *fds + z, *fds + z + 1);			//<<----☢
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
		ft_putendl_fd("gsh: parcing/syntax error", 2);
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
			gsh_count_pipes(lines + i, pps);
			fds == NULL && pps[0] ? open_all_pipes(&fds, &cp, pps[0] * 2): 0;
			ft_dprintf(2, "{%s} pps#%d\n", (lines[i])->str, pps[1]);		//<<----☢
			if (pps[1] > 1)
				fds += 2;
			gsh_seek((lines[i])->str, pps, fds);
			// ft_putendl_fd("------done------", 2);					//<<----☢
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
	gsh_r_history_bucket(-1, NULL);
	gsh_bucket(3, 0);
	system("leaks 21sh | tail -n 4");
	return (rat);
}