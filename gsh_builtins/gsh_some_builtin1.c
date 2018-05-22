/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_some_builtin1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:28:40 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/18 15:28:42 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**	CD ECHO
*/

const t_fptr	g_builtin[] = {
	{"cd", gsh_cd},
	{"echo", gsh_echo},
	{"env", gsh_env},
	{"exit", gsh_exit},
	{"help", gsh_help},
	{"history", gsh_history},
	{"set", gsh_set},
	{"setenv", gsh_setenv},
	{"setopt", gsh_setopt},
	{"unset", gsh_unset},
	{"unsetenv", gsh_unsetenv},
	{NULL, NULL}
};

int			gsh_builtin_cmd(char **cmd)
{
	unsigned			i;

	i = 0;
	while (g_builtin[i].name)
	{
		if (!ft_strcmp(g_builtin[i].name, *cmd))
			return ((g_builtin[i]).func(cmd + 1));
		i++;
	}
	return (-1);
}

static int	gsh_cd_minus(char *av, int i)
{
	char *ptr;

	if (i)
	{
		ptr = ft_strdup(gsh_get_env("OLDPWD"));
		set_add_env("OLDPWD", gsh_get_env("PWD"), ENV);
		chdir(ptr);
		ft_printf("%s\n", ptr);
		set_add_env("PWD", ptr, ENV);
		free(ptr);
	}
	else
	{
		set_add_env("OLDPWD", gsh_get_env("PWD"), ENV);
		chdir(av);
		set_add_env("PWD", av, ENV);
	}
	return (0);
}

static void	gsh_some_cd_trash(char *av)
{
	char buf[BUFSIZE + 1];

	set_add_env("OLDPWD", gsh_get_env("PWD"), ENV);
	if (!ft_strncmp(av, ".", 1) || !ft_strncmp(av, "..", 2))
	{
		getcwd(buf, BUFSIZE);
		set_add_env("PWD", buf, ENV);
	}
	else
		set_add_env("PWD", av, ENV);
}

int			gsh_cd(char **av)
{
	if (!*av || (*av && **av == '-' && *(*av + 1) == '-'))
		return (gsh_cd_minus(gsh_get_env("HOME"), 0));
	if (*av && *(av + 1))
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	else if (**av == '-' && !*(*av + 1))
		return (gsh_cd_minus(NULL, 1));
	else if (chdir(*av) == -1)
	{
		if (access(*av, F_OK))
			ft_dprintf(2, "%s%s\n", "cd: no such file or directory: ", *av);
		else if (access(*av, X_OK))
			ft_dprintf(2, "%s%s\n", "cd: permission denied: ", *av);
		else
			ft_dprintf(2, "%s%s\n", "cd: some unacceptable error: ", *av);
		return (1);
	}
	gsh_some_cd_trash(*av);
	return (0);
}

int			gsh_echo(char **av)
{
	while (*av && *(av + 1))
	{
		if (**av)
			ft_printf("%s ", *av);
		av++;
	}
	if (*av)
		ft_printf("%s", *av);
	write(1, "\n", 1);
	return (0);
}
