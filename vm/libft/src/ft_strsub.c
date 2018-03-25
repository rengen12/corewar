/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:43:21 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:43:26 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	if (!s || !(r = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (len-- && s[start])
		r[i++] = s[start++];
	r[i] = '\0';
	return (r);
}
