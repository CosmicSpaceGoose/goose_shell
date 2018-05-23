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

void		gsh_h_init_hist(char *str)
{
	char	*file;
	char	*line;
	int		fd;

	if (!str)
		file = gsh_get_env("HISTFILE");
	else
		file = str;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		g_hst_sz = (unsigned)ft_atoi(gsh_get_env("HISTSIZE"));
		while (get_next_line(fd, &line) > 0)
		{
			gsh_r_history_bucket(CREATE, 0);
			gsh_r_history_bucket(ADD, line);
			free(line);
		}
		close(fd);
	}
}

static void	gsh_init_env(void)
{
	char		*str;
	char		buf[BUFSIZE + 1];

	set_add_env("?", "0", SH);
	str = ft_itoa(getpid());
	set_add_env("$", str, SH);
	free(str);
	str = ft_strjoin(getpwuid(getuid())->pw_dir, "/.gsh_history");
	set_add_env("HISTFILE", str, SH);
	free(str);
	set_add_env("HISTSIZE", "42", SH);
	set_add_env("HISTFILESIZE", "42", SH);
	set_add_env("GRAPHICS_OUTPUT_SPEED", "50000", SH);
	set_add_env("HOME", getpwuid(getuid())->pw_dir, ENV);
	getcwd(buf, BUFSIZE);
	set_add_env("PWD", buf, ENV);
	set_add_env("OLDPWD", buf, ENV);
	if (!(str = gsh_get_env("SHLVL")))
		set_add_env("SHLVL", "1", ENV);
	else
	{
		str = ft_itoa(ft_atoi(str) + 1);
		set_add_env("SHLVL", str, ENV);
		free(str);
	}
}

static int	gsh_overwrite_env(void)
{
	char	*str;
	int		fd;
	int		rat;

	str = ft_strjoin(getpwuid(getuid())->pw_dir, "/.gshrc");
	set_add_env("GSHRC", str, SH);
	fd = open(str, O_RDONLY);
	free(str);
	if (fd != -1)
	{
		rat = 0;
		while (get_next_line(fd, &str) > 0)
		{
			(*str && *str != '#') ? gsh_pre_launch(gsh_pc_lines(str)) : 0;
			free(str);
			if ((rat = ft_atoi(gsh_get_env("?"))) > 255)
			{
				gsh_bucket(FREE_ALL, 0);
				return (rat);
			}
		}
		close(fd);
	}
	return (0);
}

int			gsh_init(void)
{
	extern char		**environ;
	extern uint32_t	g_opt_n;
	char			**envcp;
	int				i;

	i = 0;
	g_opt_n = DEFAULT_VALUE;
	while (environ[i])
		i++;
	envcp = (char **)malloc(sizeof(char *) * (i + 1));
	envcp[i] = NULL;
	while (i--)
		envcp[i] = ft_strdup(environ[i]);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINFO, SIG_IGN);
	ft_bzero((void *)g_buffer, LINE_SIZE);
	gsh_bucket(SAVE_ENV, envcp);
	gsh_std_save_restore(SAVE);
	gsh_init_env();
	i = gsh_overwrite_env();
	(g_opt_n & USE_HASH) ? gsh_init_hash_table() : 0;
	(g_opt_n & LOAD_HIST) && (g_opt_n & USE_HIST) ? gsh_h_init_hist(NULL) : 0;
	return (i);
}
