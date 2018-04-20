/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_pipes.c                                        :+:      :+:    :+:   */
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

void		make_sum_redir(char **red)
{
	char	*ptr;
	int		old;
	char	new;

	while (*red)
	{
		old = -1;
		(**red > 47 && **red < 58) ? old = **red - 48 : 0;
		if ((ptr = ft_strchr(*red, '<')))
		{
			old == -1 ? old = 0 : 0;
			new = open(ptr + 1, O_RDONLY);
		}
		else if ((ptr = ft_strchr(*red, '>')))
		{
			old == -1 ? old = 1 : 0;
			if (*(ptr + 1) == '>')
				new = open(ptr + 2, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				new = open(ptr + 1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
		dup2(new, old);
		red++;
	}
}

static int	gsh_no_pipes(t_arrs z, int *pps, int *fds)
{
	int		rat;

	if (pps[0])
	{
		close(fds[-1]);
		dup2(fds[-2], 0);
	}
	if (z.red)
		make_sum_redir(z.red);
	if ((rat = gsh_builtin_cmd(z.cmd)) == -1)
	{
		if (!ft_strchr(*(z.cmd), '/'))
			rat = gsh_os_cmd(z.cmd, gsh_get_env("PATH"));
		else
			rat = gsh_launch_cmnd(*(z.cmd), z.cmd);
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
			ft_dprintf(2, "gsh: command not found: %s\n", *cmd);
			rat = 127;
		}
		else
			rat = gsh_execute(*cmd, cmd);
	}
	return (rat);
}

/*
**		FORK FOR PIPED COMMANDS
*/

static int	gsh_pipes(t_arrs z, int pps, int *fds)
{
	int st;
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
		if (z.red)
			make_sum_redir(z.red);
		exit(gsh_pipes_exec(z.cmd));
	}
	else if (id > 0)
	{
		wait(&st);
		close(fds[1]);
		gsh_std_save_restore(RESTORE);
		return (gsh_exit_status(st, *(z.cmd)));
	}
	write(2, "gsh: Alarma!! Can't make fork!\n", 31);
	return (1);
}

/*
**		PARCE CMD & ARGUMENTS, RUN (PIPES | NO_PIPES) & SET EXIT STATUS
*/

int			gsh_seek(char *line, int *pps, int *fds)
{
	int		rat;
	char	*str;
	t_arrs	z;

	z = gsh_parcer(line);
	// if (1)										//<<-----☢
	if (!z.cmd)
	{
		// ft_free_arr((void **)z.cmd);				//<<-----☢
		ft_free_arr((void **)z.red);
		return (0);
	}
	if (pps[0] && pps[1] != END_PPL)
		rat = gsh_pipes(z, pps[1], fds);
	else
		rat = gsh_no_pipes(z, pps, fds);
	set_add_env("_", *(z.cmd));
	str = ft_itoa(rat);
	set_add_env("?", str);
	free(str);
	ft_free_arr((void **)z.cmd);
	if (z.red)
		ft_free_arr((void **)z.red);
	return (rat);
}
