/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/11 18:53:02 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void init_struct(t_pipex *pipex)
{
    pipex->infile = -1;
    pipex->outfile = -1;
    pipex->cmd1 = NULL;
    pipex->cmd2 = NULL;
    pipex->path = NULL;
    pipex->directories = NULL;
}
char	*get_env_value(char *value, char **env)       ///// fonction testée OK
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

void	get_pathname(char **cmd, t_pipex *pipex, int j)
{
	int		i;
	char	*temp;
	char *path;

	path = NULL;
	i = 0;
	temp = ft_strjoin("/", cmd[0]);
	while (pipex->directories[i])
	{
		path = ft_strjoin(pipex->directories[i], temp);
		if (access(path, X_OK) == 0)
		{
			if (j == 1)
				pipex->pathname_cmd1 = path;
			else if (j == 2)
				pipex->pathname_cmd2 = path;
			break ;
		}
		free(path);
		i++;
	}
	free(temp);
}

void    init_pipex(t_pipex *pipex, char **av, char **env)
{ 
    pipex->infile = open(av[1], O_RDONLY);
    if (pipex->infile == -1)
        perror("Opening infile");
    pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile == -1)
        perror("Opening or creating outfile");
    pipex->cmd1 = ft_split(av[2], ' ');
    if (!pipex->cmd1)
    	exit_with_message_and_free("Error\nSplit cmd1", pipex);
    pipex->cmd2 = ft_split(av[3], ' ');
    if (!pipex->cmd2)
    	exit_with_message_and_free("Error\nSplit cmd2", pipex);
    pipex->path = get_env_value("PATH=", env);							/////// test OK
	if (pipex->path == NULL)
		exit_with_message_and_free("Unable to get PATH", pipex);
    pipex->directories = ft_split(pipex->path, ':');					/////// test OK
    if (!pipex->directories)
    	exit_with_message_and_free("Error\nSplit directories", pipex);  // modifier msg
    get_pathname(pipex->cmd1, pipex, 1);								/////// test OK
    get_pathname(pipex->cmd2, pipex, 2);								/////// test OK
    if (!pipex->cmd1 || !pipex->cmd2)
		exit_with_message_and_free("Non existing command", pipex);
    // prevoir des exit et erreurs en cas de chaine nulle
}
