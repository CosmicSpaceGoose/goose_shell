/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:36:41 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/06 13:36:44 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void	gsh_init_env(void)
{
	char		*str;
	char		buf[BUFSIZE + 1];

	set_add_env("?", "0");
	set_add_env("HOME", getpwuid(getuid())->pw_dir);
	getcwd(buf, BUFSIZE);
	set_add_env("PWD", buf);
	set_add_env("OLDPWD", buf);
	str = ft_itoa(getpid());
	set_add_env("$", str);
	free(str);
	if (!(str = gsh_get_env("SHLVL")))
		set_add_env("SHLVL", "1");
	else
	{
		str = ft_itoa(ft_atoi(str) + 1);
		set_add_env("SHLVL", str);
		free(str);
	}
}

void		gsh_init(int i)
{
	extern char	**environ;
	char		**envcp;

	while (environ[i])
		i++;
	envcp = (char **)malloc(sizeof(char *) * (i + 1));
	envcp[i] = NULL;
	while (i--)
		envcp[i] = ft_strdup(environ[i]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINFO, SIG_IGN);
	gsh_bucket(1, envcp);
	gsh_std_save_restore(SAVE);
	gsh_init_env();
}

void		gsh_std_save_restore(int mod)
{
	static int	std[3];

	if (mod)
	{
		std[0] = dup(0);
		std[1] = dup(1);
		std[2] = dup(2);
	}
	else
	{
		dup2(std[0], 0);
		dup2(std[1], 1);
		dup2(std[2], 2);
	}
}
