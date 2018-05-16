/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:56:32 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/14 16:56:33 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

void	gsh_end(void)
{
	gsh_delete_hash_table();
	gsh_r_history_bucket(ERASE, NULL);
	gsh_bucket(FREE_ALL, 0);
	system("leaks 21sh | tail -n 4");
}
