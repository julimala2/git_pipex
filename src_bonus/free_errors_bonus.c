/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:11:29 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/20 17:05:38 by jmalaval         ###   ########.fr       */
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

void	free_tab(char **tab)
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

void	free_struct(t_pipex_b *pipex)
{
	if (pipex)
	{
		if (pipex->directories)
			free_tab(pipex->directories);
		if (pipex->path)
			free(pipex->path);
		if (pipex->pathname_cmd1)
			free(pipex->pathname_cmd1);
		if (pipex->pathname_cmd2)
			free(pipex->pathname_cmd2);
		if (pipex->cmd1)
			free_tab(pipex->cmd1);
		if (pipex->cmd2)
			free_tab(pipex->cmd2);
		free(pipex);
	}
}
