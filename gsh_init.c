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
#include "gsh_reader.h"

static void	gsh_init_env(void)
{
	char		*str;
	char		buf[BUFSIZE + 1];

	set_add_env("?", "0", SH);
	set_add_env("HOME", getpwuid(getuid())->pw_dir, ENV);
	getcwd(buf, BUFSIZE);
	set_add_env("PWD", buf, ENV);
	set_add_env("OLDPWD", buf, ENV);
	str = ft_itoa(getpid());
	set_add_env("$", str, SH);
	free(str);
	if (!(str = gsh_get_env("SHLVL")))
		set_add_env("SHLVL", "1", ENV);
	else
	{
		str = ft_itoa(ft_atoi(str) + 1);
		set_add_env("SHLVL", str, ENV);
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
	// signal(SIGQUIT, SIG_IGN);					//EMERGENCY EXIT ON!!!
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINFO, SIG_IGN); 
	ft_bzero((void *)g_buffer, LINE_SIZE);
	gsh_bucket(SAVE_ENV, envcp);
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

void		gsh_readmoar_atzero(char **line)
{
	char *ptr;
	char *tmp;

	gsh_reader(&tmp, write(0, "> ", 2));
	ptr = ft_strsub(*line, 0, ft_strlen(*line) - 1);
	free(*line);
	*line = ft_strjoin(ptr, tmp);
	free(tmp);
	free(ptr);
}
