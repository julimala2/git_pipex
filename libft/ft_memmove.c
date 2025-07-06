/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:58:53 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/03 16:31:42 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned long	i;
	unsigned char	*t_dest;
	unsigned char	*t_src;

	i = 0;
	t_dest = (unsigned char *)dest;
	t_src = (unsigned char *)src;
	if (t_dest > t_src)
	{
		while (n > 0)
		{
			n--;
			t_dest[n] = t_src[n];
		}
	}
	else
	{
		ft_memcpy(t_dest, t_src, n);
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s1[6] = "Hello";
	char s2[6] = "Hello";
	char d1[6];
	char d2[6];

	printf("Avant ft_memmove : %s\n", s1);
	printf("Apres ft_memmove : %s\n", (char *)ft_memmove(d1, s1, 3));
	printf("Apres memmove : %s", (char *)memmove(d2, s2, 3));
}*/
