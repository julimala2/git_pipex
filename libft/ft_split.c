/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:25:52 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/01 14:47:22 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countlines(const char *s, char c)
{
	int	count;
	int	i;

	if (!s)
		return (0);
	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	if (s[i - 1] == c)
		count++;
	return (count);
}

static char	**ft_fill_tab(char **tab, const char *str, char c, int w)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (x < w)
	{
		while (str[i] && str[i] == c)
			i++;
		j = i;
		while (str[j] && str[j] != c)
			j++;
		tab[x] = (ft_substr(str, i, (j - i)));
		if (!tab[x])
			free(tab[x]);
		i = j;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	int		w;
	int		x;
	char	**tab;

	if (!s)
		return (NULL);
	x = 0;
	w = ft_countlines(s, c);
	tab = malloc((w + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (w == 0)
	{
		tab[x] = NULL;
		return (tab);
	}
	ft_fill_tab(tab, s, c, w);
	return (tab);
}
