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
	char		*env;
	char		*ptr;
	char		**environ;
	int			i;

	i = 0;
	if ((environ = gsh_bucket(RETURN_ENV, 0)))
		while (environ[i])
		{
			ptr = ft_strchr(environ[i], '=');
			env = ft_strsub(environ[i], 0, ptr - environ[i]);
			if (ft_strcmp(name, env) == 0)
			{
				free(env);
				return (ptr + 1);
			}
			free(env);
			i++;
		}
	i = 0;
	if ((environ = gsh_bucket(RETURN_SH, 0)))
		while (environ[i])
		{
			ptr = ft_strchr(environ[i], '=');
			env = ft_strsub(environ[i], 0, ptr - environ[i]);
			if (ft_strcmp(name, env) == 0)
			{
				free(env);
				return (ptr + 1);
			}
			free(env);
			i++;
		}
	return (NULL);
}

int			gsh_unsetenv(char **av)
{
	int		i;
	char	**environ;

	if (!*av)
	{
		ft_dprintf(2, "%s", "unsetenv: Too few arguments.\n");
		return (1);
	}
	while (*av)
	{
		if ((i = set_brwse_env(*av, ENV)) == -1)
		{
			av++;
			continue ;
		}
		environ = gsh_bucket(RETURN_ENV, 0);
		free(environ[i]);
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
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
