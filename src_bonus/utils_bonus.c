/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/24 17:39:31 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	init_struct(t_pipex_b *pipex, char **av)
{
	pipex->infile = -1;
	if (access(av[1], F_OK) == 0 && access(av[1], R_OK) < 0)
		pipex->infile = 0;
	else
	{
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile == -1)
			perror("Opening infile");
	}
	pipex->outfile = -1;
	pipex->cmd = NULL;
	pipex->path = NULL;
	pipex->directories = NULL;
	pipex->outfile_error = 1;
	pipex->pathname_cmd = NULL;
	pipex->last_cmd = 0;
	pipex->first_cmd = 0;
	pipex->prev_fd = -1;
	pipex->pids = malloc(pipex->cmd_count * sizeof(pid_t));
	if (!pipex->pids)
		exit_with_message_and_free("Malloc pids", pipex, 1);
}

char	*get_env_value(char *value, char **env)
{
	size_t	len_value;
	size_t	i;

	len_value = ft_strlen(value);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], value, len_value) == 0)
			return (ft_strdup(env[i] + len_value));
		i++;
	}
	return (NULL);
}

void	get_pathname(char **cmd, t_pipex_b *pipex)
{
	int		i;
	char	*temp;
	char	*path;

	path = NULL;
	i = 0;
	temp = ft_strjoin("/", cmd[0]);
	while (pipex->directories[i])
	{
		path = ft_strjoin(pipex->directories[i], temp);
		if (access(path, X_OK) == 0)
		{
			pipex->pathname_cmd = path;
			break ;
		}
		free(path);
		i++;
	}
	free(temp);
}

void	init_pipex(t_pipex_b *pipex, char *av, char **env)
{
	pipex->cmd = ft_split(av, ' ');
	if (!pipex->cmd)
		exit_with_message_and_free("Split cmd", pipex, 1);
	pipex->path = get_env_value("PATH=", env);
	if (pipex->path == NULL)
		exit_with_message_and_free("Unable to get PATH", pipex, 1);
	pipex->directories = ft_split(pipex->path, ':');
	if (!pipex->directories)
		exit_with_message_and_free("Split directories", pipex, 1);
	get_pathname(pipex->cmd, pipex);
}

void	init_outfile(t_pipex_b *pipex)
{
	if (access(pipex->path_outfile, F_OK) < 0)
	{
		pipex->outfile = open(pipex->path_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		pipex->outfile_error = 0;
	}
	else
	{
		if (access(pipex->path_outfile, W_OK) < 0)
			perror("Access outfile");
		else
		{
			pipex->outfile = open(pipex->path_outfile, O_WRONLY | O_TRUNC);
			pipex->outfile_error = 0;
		}

	}
	if (pipex->outfile == -1)
		perror("Opening or creating outfile");
}
