/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:08:20 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/04 16:34:09 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

int	existing_cmd(char *cmd, char **dir)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	if (ft_strchr(cmd, '-'))
	{
		while (cmd[i] != ' ')
			i++;
		temp = ft_substr(cmd, 0, i);
	}
	else
		temp = ft_strdup(cmd);
	i = 0;
	while (dir[i])
	{
		path = ft_strjoin(dir[i], temp);
		if (access(path, X_OK) == 0)
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	free(temp);
	return (0);
}

// verifier que outfile existe --> sinon le créer