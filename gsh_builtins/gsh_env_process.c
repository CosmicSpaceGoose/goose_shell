/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_env_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:02:34 by dlinkin           #+#    #+#             */
/*   Updated: 2018/02/12 15:02:35 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		ENV COMMAND
*/

int			gsh_list_env(void)
{
	char	**environ;
	int		i;

	i = 0;
	if ((environ = *gsh_bucket(RETURN, 0)))
	{
		while (environ[i])
		{
			ft_putendl(environ[i]);
			i++;
		}
	}
	return (0);
}

static int	env_process(char ***av, char *c, char *path)
{
	int		rat;
	char	*name;
	char	*ptr;

	rat = 0;
	ft_strcpy(path, gsh_get_env("PATH"));
	if ((rat = env_read_flags(av, c, path)))
		return (rat);
	while (**av && (ptr = ft_strchr(**av, '=')))
	{
		name = ft_strsub(**av, 0, ptr - **av);
		set_add_env(name, ptr + 1);
		free(name);
		(*av)++;
	}
	return (0);
}

static int	env_usage(int err, char c)
{
	if (err == 1)
		ft_dprintf(2, "%s%c\n", "env: illegal option -- ", c);
	else if (err == 2)
		ft_dprintf(2, "%s%c\n", "env: option requires an argument -- ", c);
	ft_dprintf(2, "%s", "usage: env [-i] [-u name] [name=value .\
..] [utility [argument ...]]\n");
	return (1);
}

static int	env_launch(char **av)
{
	char	c;
	char	path[NAMESIZE];
	int		st;
	int		id;

	path[0] = 0;
	if ((id = env_process(&av, &c, path)) > 0)
		st = env_usage(id, c);
	else
	{
		if (!*av)
			st = gsh_list_env();
		else
		{
			if (gsh_get_env("PATH"))
				ft_strcpy(path, gsh_get_env("PATH"));
			if (!ft_strchr(*av, '/'))
				st = gsh_os_cmd(av, path);
			else
				st = gsh_launch_cmnd(*av, av);
		}
	}
	gsh_bucket(FREE, 0);
	exit(st);
}

int			gsh_env(char **av)
{
	int			id;
	int			st;

	id = fork();
	if (id == 0)
		exit(env_launch(av));
	else if (id > 0)
	{
		wait(&st);
		return (gsh_exit_status(st, *av));
	}
	ft_dprintf(2, "env: Alarma!! Can't make fork!\n");
	return (1);
}
