/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 11:48:35 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/26 11:48:36 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	size_t i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
		write(1, s, i);
	}
	write(1, "\n", 1);
}
