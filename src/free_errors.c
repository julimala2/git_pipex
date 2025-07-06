/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:11:29 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/06 17:56:08 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_with_message(char *str)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	free_tab(char **tab)
{
	int i; 
	
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}