/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:10:13 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/21 18:10:14 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"
#include "gsh_sgnl.h"

/*
**		CHECK COMMAND NAMES 'ERE
*/

int		gsh_get_path_name(char *out, char *path, char *name)
{
	char	*tmp;
	int		ret;

	ft_bzero((void *)out, NAMESIZE);
	if (!(tmp = ft_strchr(path, ':')))
	{
		ret = ft_strlen(path);
		ft_strncpy(out, path, ret);
	}
	else
	{
		if (*path == 0)
			return (0);
		ft_strncpy(out, path, tmp - path);
		ret = tmp - path;
	}
	ft_strcat(out, "/");
	ft_strcat(out, name);
	return (ret);
}

int		gsh_exit_status(int status, char *name)
{
	extern const char	*g_sig[32];
	int					i;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status))
		{
			i = WTERMSIG(status);
			if (i > 2 && i < 33)
				ft_dprintf(2, "%s%s\n", g_sig[WTERMSIG(status) - 1], name);
			return (128 + WTERMSIG(status));
		}
		if (WCOREDUMP(status))
			return (128 + WCOREDUMP(status));
	}
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (0);
}

int		gsh_execute(char *cmd, char **av)
{
	if (!access(cmd, F_OK))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		execve(cmd, av, gsh_bucket(RETURN_ENV, 0));
		ft_dprintf(2, "|< permission denied: %s\n", cmd);
		return (126);
	}
	ft_dprintf(2, "|< command not found: %s\n", cmd);
	return (127);
}

int		gsh_launch_cmnd(char *cmd, char **av)
{
	int			id;
	int			st;

	id = fork();
	if (id == 0)
		exit(gsh_execute(cmd, av));
	else if (id > 0)
	{
		wait(&st);
		return (gsh_exit_status(st, cmd));
	}
	write(2, "|< Alarma!! Can't make fork!\n", 29);
	return (1);
}

int		gsh_os_cmd(char **cmd, char *path)
{
	char			name[NAMESIZE];
	char			*str;
	int				i;
	extern uint32_t	g_opt_n;

	if ((g_opt_n & USE_HASH) && (str = gsh_hash_search(*cmd)))
		return (gsh_launch_cmnd(str, cmd));
	while ((i = gsh_get_path_name(name, path, *cmd)))
	{
		if (!access(name, F_OK))
			return (gsh_launch_cmnd(name, cmd));
		path += i;
		if (*path)
			path++;
	}
	ft_dprintf(2, "|< command not found: %s\n", *cmd);
	return (127);
}
