/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/09 23:17:20 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Function to check if the input file is valid
int	verify_input(int argc, char **argv)
{
	int	full;

	if (argc != 2)
	{
		printf("Usage: %s <filename>.fdf\n", argv[0]);
		return (EXIT_FAILURE);
	}
	full = ft_strlen(argv[1]);
	if (full <= 4)
	{
		printf("Not valid file. Needs to be of type .fdf\n");
		return (EXIT_FAILURE);
	}
	if ((argv[1][full - 1] == 'f' && argv[1][full - 2] == 'd') && (argv[1][full
			- 3] == 'f' && argv[1][full - 4] == '.'))
		if (full > 4 && ft_isalnum(argv[1][full - 5]))
			return (EXIT_SUCCESS);
	printf("Not valid file. Needs to be of type .fdf\n");
	return (EXIT_FAILURE);
}

// Main entry point
int	main(int argc, char **argv)
{
	t_map	map;

	if (verify_input(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_map(&map);
	map.ptr_server_mlx = mlx_init();
	if (!map.ptr_server_mlx)
		return (EXIT_FAILURE);
	if (scan_file(&map, argv[1]) == EXIT_FAILURE)
	{
		clean_up(&map);
		return (EXIT_FAILURE);
	}
	initialize_window(&map);
	clean_up(&map);
	return (EXIT_SUCCESS);
}
