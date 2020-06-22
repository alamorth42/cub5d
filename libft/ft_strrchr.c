/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:06:38 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = -1;
	ptr = (char *)s;
	while (ptr[++i])
		;
	while (i >= 0)
	{
		if (ptr[i] == (char)c)
			return (ptr + i);
		i--;
	}
	return ((char *)0);
}
