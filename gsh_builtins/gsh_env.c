/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:28:48 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/18 15:28:49 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

char		*gsh_get_env(char *name)
{
	char	*env;
	char	*ptr;
	char	**environ;
	char	*rat;

	rat = NULL;
	if ((environ = gsh_bucket(RETURN_ENV, 0)))
		while (*environ)
		{
			ptr = ft_strchr(*environ, '=');
			env = ft_strsub(*environ, 0, ptr - *environ);
			!ft_strcmp(name, env) ? rat = ptr + 1 : 0;
			free(env);
			environ++;
		}
	if ((environ = gsh_bucket(RETURN_SH, 0)))
		while (*environ)
		{
			ptr = ft_strchr(*environ, '=');
			env = ft_strsub(*environ, 0, ptr - *environ);
			!ft_strcmp(name, env) ? rat = ptr + 1 : 0;
			free(env);
			environ++;
		}
	return (rat);
}

int			gsh_unsetenv(char **av)
{
	int				i;
	char			**environ;
	extern uint32_t	g_opt_n;

	if (!*av)
	{
		ft_dprintf(2, "%s", "unsetenv: Too few arguments.\n");
		return (1);
	}
	while (*av)
	{
		if ((i = set_brwse_env(*av, ENV)) != -1)
		{
			environ = gsh_bucket(RETURN_ENV, 0);
			free(environ[i]);
			while (environ[i++])
				environ[i - 1] = environ[i];
		}
		if ((g_opt_n & USE_HASH) && (g_opt_n & UPD_HASH)
		&& !ft_strcmp(*av, "PATH"))
			gsh_delete_hash_table();
		av++;
	}
	return (0);
}

char		**gsh_bucket(int mod, char **in)
{
	static char	**env;
	static char	**sh;

	if (mod == SAVE_ENV)
		env = in;
	else if (mod == SAVE_SH)
		sh = in;
	else if (mod & 1)
	{
		if ((mod == FREE_ENV || mod == FREE_ALL) && env)
		{
			ft_free_arr((void **)(env));
			env = NULL;
		}
		if ((mod == FREE_SH || mod == FREE_ALL) && sh)
		{
			ft_free_arr((void **)(sh));
			sh = NULL;
		}
	}
	else if (mod == RETURN_SH)
		return(sh);
	return (env);
}
