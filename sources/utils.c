/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:44:47 by marvin            #+#    #+#             */
/*   Updated: 2025/03/03 18:44:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	init_structs(t_img *dest_cds, t_src *three_d_cds)
{
	dest_cds->x = 0;
	dest_cds->y = 0;
	three_d_cds->x_row = 0;
	three_d_cds->y_column = 0;
	three_d_cds->z_value = 0;
}
