/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_pre_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:05:46 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/08 18:05:47 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		PIPES (C.O.) & REDIRECTIONS
*/

static int	gsh_no_pipes(t_orba *zee, int *pps, int *fds)
{
	int	rat;

	if (pps[0])
	{
		close(fds[-1]);
		dup2(fds[-2], 0);
	}
	if (zee->red && gsh_make_sum_redir(zee->red))
	{
		gsh_std_save_restore(RESTORE);
		return (0);
	}
	if ((rat = gsh_builtin_cmd(zee->cmd)) == -1)
	{
		if (!ft_strchr(*(zee->cmd), '/'))
			rat = gsh_os_cmd(zee->cmd, gsh_get_env("PATH"));
		else
			rat = gsh_launch_cmnd(*(zee->cmd), zee->cmd);
	}
	if (!isatty(0) || !isatty(1) || !isatty(2))
		gsh_std_save_restore(RESTORE);
	return (rat);
}

static int	gsh_pipes_exec(char **cmd)
{
	int		rat;
	char	name[NAMESIZE];
	int		i;
	char	*path;

	if ((rat = gsh_builtin_cmd(cmd)) == -1)
	{
		if (!ft_strchr(*cmd, '/'))
		{
			path = gsh_get_env("PATH");
			while ((i = gsh_get_path_name(name, path, *cmd)))
			{
				if (!access(name, F_OK))
					return (gsh_execute(name, cmd));
				path += i;
				if (*path)
					path++;
			}
			ft_dprintf(2, "|< command not found: %s\n", *cmd);
			rat = 127;
		}
		else
			rat = gsh_execute(*cmd, cmd);
	}
	return (rat);
}

/*
**		FORK FOR PIPED COMMANDS			//watch gsh_graphics.c:100
*/

static int	gsh_pipes(t_orba *z, int pps, int *fds)
{
	int id;

	if (!(id = fork()))
	{
		close(fds[0]);
		dup2(fds[1], 1);
		if (pps == MIDDLE_PPL)
		{
			close(fds[-1]);
			dup2(fds[-2], 0);
		}
		if (z->red && gsh_make_sum_redir(z->red))
			exit(0);
		exit(gsh_pipes_exec(z->cmd));
	}
	else if (id > 0)
	{
		close(fds[1]);
		close(fds[-2]);
		return (0);
	}
	write(2, "|< Alarma!! Can't make fork!\n", 31);
	return (1);
}

/*
**		RUN (PIPES | NO_PIPES) & SET EXIT STATUS
*/

int			gsh_seek(t_orba *zee, int *pps, int *fds)
{
	int		rat;
	char	*str;

	if (!zee->cmd && !zee->red)
		return (0);
	if (!*(zee->cmd) && zee->red)
		return (gsh_write_some_files(zee->red, 0));
	if (pps[0] && pps[1] != END_PPL)
		rat = gsh_pipes(zee, pps[1], fds);
	else
		rat = gsh_no_pipes(zee, pps, fds);
	set_add_env("_", *(zee->cmd), ENV);
	str = ft_itoa(rat);
	set_add_env("?", str, SH);
	free(str);
	return (rat);
}
