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
**		PIPES (C.O.)
*/

static int	gsh_no_pipes(t_arrs z, int *pipes, int *fds)
{
	int		rat;

	if (pipes[0])
	{
		close(*(fds - 1));
		dup2(*(fds - 2), 0);
	}
	if (z.red)
		write(1, "!", 1);
		//gsh_make_some_redirections(z.red);
	if ((rat = gsh_builtin_cmd(z.cmd)) == -1)
	{
		if (!ft_strchr(*(z.cmd), '/'))
			rat = gsh_os_cmd(z.cmd, gsh_get_env("PATH"));
		else
			rat = gsh_launch_cmnd(*(z.cmd), z.cmd);
	}
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

static int	gsh_pipes(t_arrs z, int pipes, int *fds)
{
	int st;
	int id;

	if (!(id = fork()))
	{
		if (z.red)
			write(1, "!", 1);
			//gsh_make_some_redirections(red);
		close(*fds);
		dup2(*(fds + 1), 1);
		if (pipes == 2)
		{
			close(*(fds - 1));
			dup2(*(fds - 2), 0);
		}
		exit(gsh_pipes_exec(z.cmd));
	}
	else if (id > 0)
	{
		wait(&st);
		close(*(fds + 1));
		if (!WIFEXITED(st))
			return (gsh_exit_status(st, *(z.cmd)));
		return (WEXITSTATUS(st));
	}
	ft_dprintf(2, "gsh: Alarma!! Can't make fork!\n");
	return (1);
}

int			gsh_seek(char *line, int *pipes, int *fds)
{
	int		rat;
	char	*str;
	t_arrs	z;

	z = gsh_parcer(line);
	if (!z.cmd)
		return (0);
	if (pipes[0] && pipes[1] != 3)
		rat = gsh_pipes(z, pipes[1], fds);
	else
		rat = gsh_no_pipes(z, pipes, fds);
	set_add_env("_", *(z.cmd));
	str = ft_itoa(rat);
	set_add_env("?", str);
	free(str);
	ft_free_arr((void **)z.cmd);
	if (z.red)
		ft_free_arr((void **)z.red);
	return (rat);
}
