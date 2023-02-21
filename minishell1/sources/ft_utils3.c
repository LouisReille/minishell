/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:02:44 by lreille           #+#    #+#             */
/*   Updated: 2023/02/19 08:27:17 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptrdst;
	const char	*ptrsrc;

	ptrdst = dst;
	ptrsrc = src;
	if (!dst && !src)
		return (0);
	while (n--)
		*ptrdst++ = *ptrsrc++;
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return ((void *) ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *b;

	b = (unsigned char *)s;
	while (n > 0)
	{
		*b++ = '\0';
		n--;
	}
}

int		ft_contains_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
