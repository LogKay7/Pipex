/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkailany <lkailany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:04:30 by lkailany          #+#    #+#             */
/*   Updated: 2022/04/16 12:08:18 by lkailany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	ft_countwords(char const *s, char c)
{
	int	count;
	int	newpart;

	newpart = 0;
	count = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s != c && newpart == 0)
		{
			count++;
			newpart = 1;
		}
		else if (*s == c)
			newpart = 0;
		s++;
	}
	return (count);
}

static int	ft_countchar(char const *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start] != c && s[start] != '\0')
	{
		len++;
		start++;
	}
	return (len);
}

static char	**ft_free_split(char **dst, int numword)
{
	while (numword > 0)
	{
		numword--;
		free(dst[numword]);
	}
	free(dst);
	return (0);
}

static char	**ft_setwords(char const *s, char c, char **dest, int nbwords)
{
	int	i;
	int	numword;
	int	j;
	int	size;

	numword = 0;
	i = 0;
	while (s[i] != 0 && numword < nbwords)
	{
		j = 0;
		while (s[i] == c)
			i++;
		size = sizeof(char) * ft_countchar(s, c, i);
		dest[numword] = (char *) malloc(size + 1);
		if (!dest[numword])
			return (ft_free_split(dest, numword));
		while (s[i] != c && s[i] != '\0')
		{
			dest[numword][j++] = s[i++];
		}
		dest[numword++][j] = '\0';
	}
	dest[numword] = 0;
	return (dest);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		nbwords;

	if (!s)
		return (0);
	nbwords = ft_countwords(s, c);
	res = (char **) malloc(sizeof(char *) * (nbwords + 1));
	if (!res)
		return (0);
	return (ft_setwords(s, c, res, nbwords));
}
