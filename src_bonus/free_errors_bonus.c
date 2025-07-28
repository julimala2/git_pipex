/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:11:29 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/28 16:26:18 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exit_with_message(char *str, const char *str2, int n)
{
	ft_putendl_fd("Error\n", 2);
	if (str)
		ft_putendl_fd(str, 2);
	if (str2)
		perror(str2);
	exit(n);
}

void	free_tab(void **tab)	// void ? 
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_with_message_and_free(char *str, t_pipex_b *pipex, int n)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	free_struct(pipex);
	exit(n);
}

void	free_cmd(t_pipex_b *pipex)
{
	if (pipex)
	{
		if (pipex->cmd)
			free_tab((void*)pipex->cmd);
	}
}

void	free_struct(t_pipex_b *pipex)
{
	if (pipex)
	{
		if (pipex->directories)
			free_tab((void*)pipex->directories);
		if (pipex->path)
			free(pipex->path);
		if (pipex->pathname_cmd)
			free(pipex->pathname_cmd);
		free_cmd(pipex);
		if (pipex->pid)
			free_tab((void*)pipex->pid);
		free(pipex);
	}
}

