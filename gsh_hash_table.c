/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_hash_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:03:05 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/14 18:03:06 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"
#include "gsh_hash.h"

static unsigned	hash_func(char *str)
{
	unsigned i;
	unsigned n;

	i = 0;
	n = 1;
	while (*str)
	{
		i += ((unsigned)*str - 31) * ((unsigned)*str - 31) * n;
		str++;
		n++;
	}
	return (i % TABLE_SIZE);
}

static void		func(char *name)
{
	DIR				*papka;
	struct dirent	*file;
	unsigned		key;

	if (!(papka = opendir(name)))
		return ;
	while ((file = readdir(papka)))
	{
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
		{
			key = hash_func(file->d_name);
			if (g_arr[key])
			{
				while (g_arr[key])
				{
					if (ft_strcmp(file->d_name, g_arr[key][0]))
						key = (key + 1) % TABLE_SIZE;
					else
						break ;
				}
			}
			if (!g_arr[key])
			{
				g_arr[key] = (char **)malloc(sizeof(char *) * 2);
				g_arr[key][0] = ft_strdup(file->d_name);
				g_arr[key][1] = ft_strjoin(name, file->d_name);
			}
		}
	}
	closedir(papka);
}

void			gsh_init_hash_table(void)
{
	char	*path;
	char	name[1024];
	int		i;

	if (TABLE_SIZE > 5000)
	{
		g_arr = (char ***)malloc(sizeof(char **) * (TABLE_SIZE + 1));
		path = gsh_get_env("PATH");
		i = 0;
		while (i <= TABLE_SIZE)
		{
			g_arr[i] = NULL;
			i++;
		}
		while ((i = gsh_get_path_name(name, path, "")))
		{
			func(name);
			path += i;
			if (*path)
				path++;
		}
	}
	else
		g_arr = NULL;
}

char			*gsh_hash_search(char *str)
{
	unsigned key;

	if (!g_arr)
		return (NULL);
	key = hash_func(str);
	while (g_arr[key])
	{
		if (!ft_strcmp(str, g_arr[key][0]))
			return (g_arr[key][1]);
		else
			key = (key + 1) % TABLE_SIZE;
	}
	return (NULL);
}

void			gsh_delete_hash_table(void)
{
	unsigned i;

	i = 0;
	if (!g_arr)
		return ;
	while (i <= TABLE_SIZE)
	{
		if (g_arr[i])
		{
			free(g_arr[i][0]);
			free(g_arr[i][1]);
			free(g_arr[i]);
		}
		i++;
	}
	free(g_arr);
	g_arr = NULL;
}