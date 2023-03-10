/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:37:44 by rturker           #+#    #+#             */
/*   Updated: 2022/10/11 11:12:30 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char const *s, char c)
{
	size_t	i;
	int		words;
	int		important;

	i = 0;
	words = 0;
	important = 0;
	while (s[i])
	{
		if (s[i] != c && important == 0)
		{
			important = 1;
			words++;
		}
		else if (s[i] == c)
			important = 0;
		i++;
	}
	return (words);
}

static char	*word_create(char *s, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = word_counter(s, c);
	j = 0;
	split = (char **)malloc((i + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			split[j++] = word_create((char *)&s[i], c);
			while (s[i] != c && s[i])
				i++;
		}
	}
	split[j] = 0;
	return (split);
}
/*
int		main(void)
{
	char	test[] = "	 aa testi ,, kelime sayii bul hadi";
	char **tab;
	tab = ft_split(test,' ');
	int i = 0;
	int sayac = word_counter(test,' ');
	while(i < sayac)
		printf("%s\n",tab[i++]);
	return (0);
}
*/
