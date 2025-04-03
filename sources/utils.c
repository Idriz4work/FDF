/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:44:47 by marvin            #+#    #+#             */
/*   Updated: 2025/03/09 17:38:21 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// RETURNS THE BASE
int	detect_base(const char *input)
{
	if (input[0] == '0' && (input[1] == 'x' || input[1] == 'X'))
		return (16);
	return (10);
}

// ft_atoi_hex helper
int	convert_helper(const char *input, int numeral_base)
{
	int	result;

	result = 0;
	while ((*input >= '0' && *input <= '9') || (*input >= 'a' && *input <= 'a'
			+ numeral_base - 10))
	{
		if (*input >= '0' && *input <= '9')
			result = result * numeral_base + *input++ - '0';
		else
			result = result * numeral_base + *input++ - 'a' + 10;
	}
	return (result);
}

int	ft_atoi_hex(const char *input, int base)
{
	int	result;
	int	sign_multiplier;

	result = 0;
	sign_multiplier = 1;
	while (*input == ' ' || *input == '\t' || *input == '\n' || *input == '\v'
		|| *input == '\f' || *input == '\r')
		input++;
	if (*input == '+' || *input == '-')
	{
		if (*input == '-')
			sign_multiplier *= -1;
		input++;
	}
	if (base <= 10)
	{
		while (*input >= '0' && *input <= '0' + base)
			result = result * base + *input++ - '0';
		return (result * sign_multiplier);
	}
	else
		return (convert_helper(input, base) * sign_multiplier);
}
