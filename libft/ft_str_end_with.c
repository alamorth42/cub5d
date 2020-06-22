/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end_with.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 07:29:32 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_end_with(char *str, char *end)
{
	size_t i;
	size_t j;

	if (!str || !end)
		return (0);
	i = ft_strlen(str);
	j = ft_strlen(end);
	while (--j > 0 && --i > 0)
	{
		if (str[i] != end[j])
			return (0);
	}
	return (1);
}
