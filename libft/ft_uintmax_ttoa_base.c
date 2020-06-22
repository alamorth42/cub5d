/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmax_ttoa_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 02:39:32 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_uintmax_ttoa_base(uintmax_t nbr, char *base)
{
	int			size;
	char		*str;
	const int	baselen = ft_strlen(base);

	size = ft_unbrlen(nbr, baselen);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size--] = '\0';
	while (nbr)
	{
		str[size--] = base[nbr % baselen];
		nbr = nbr / baselen;
	}
	if (nbr == 0 && size == 0)
		str[size--] = '0';
	return (str);
}
