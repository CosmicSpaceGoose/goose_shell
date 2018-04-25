/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_some_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:43:35 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/22 16:43:36 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			make_sum_redir(t_redir **red)
{
	int		new;

	while (*red)
	{
		ft_putendl_fd("HALLO", 2);
		if ((*red)->io != 'I' && (*red)->ptr)
			new = open((*red)->ptr, (*red)->flgs, 0666);
		else if (!(*red)->ptr)
			new = (*red)->new;
		if (new != -1)
			dup2(new, (*red)->old);
		else
			close((*red)->old);
		red++;
	}
	return (0);
}
