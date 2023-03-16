/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleggeri <nleggeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:23:05 by nleggeri          #+#    #+#             */
/*   Updated: 2023/01/17 14:07:34 by nleggeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	percent_u(unsigned int n, int i)
{
	if (n < 0)
		n = 4294967295 - n + 1;
	if (n >= 10)
		i = percent_u(n / 10, i);
	percent_c(n % 10 + '0');
	i++;
	return (i);
}
