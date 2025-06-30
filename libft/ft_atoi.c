/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:19:26 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/06/24 15:51:19 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_atoi(const char *str, int *flag)
{
        int     re;
        int     i;

        i = 0;
        re = 0;
        if (str[i] >= '0' && str[i] <= '9')
        {
                while (str[i])
                {
                        if ((re > ((INT_MAX - (str[i] - '0')) / 10)) || str[i] < '0'
                                || str[i] > '9')
                        {
                                *flag = 1;
                                break ;
                        }
                        re = (re * 10) + (str[i] - '0');
                        i++;
                }
        }
        else
                *flag = 1;
        return (re);
}
