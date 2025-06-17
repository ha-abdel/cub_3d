/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:21:28 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/04/29 13:24:32 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countspace(long n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count++;
		return (count);
	}
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*ft_rev(char *arr, int sign)
{
	int		i;
	int		len;
	char	swap;

	len = ft_strlen(arr);
	i = sign;
	len = len - 1;
	while (i < len)
	{
		swap = arr[len];
		arr[len] = arr[i];
		arr[i] = swap;
		i++;
		len--;
	}
	return (arr);
}

static char	*checknbr(long nb, char *arr, int *sign)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		arr[i++] = '-';
		*sign = 1;
		nb = -nb;
	}
	if (nb == 0)
	{
		arr[0] = '0';
		arr[1] = '\0';
		return (arr);
	}
	while (nb > 0)
	{
		arr[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_itoa(int n)
{
	char	*arr;
	long	nb;
	int		sign;

	nb = n;
	sign = 0;
	arr = ft_malloc(countspace(nb) + 1, 1);
	if (!arr)
		return (NULL);
	arr = checknbr(nb, arr, &sign);
	return (ft_rev(arr, sign));
}
