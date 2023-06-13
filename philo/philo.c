/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 05:44:49 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/13 13:52:56 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, int *ac, int **av)
{
	*av = argv_getint(ac, argv);
	if ((!*av && argc > 1) || (*ac > 0 && (*av)[0] <= 0))
	{
		printf("Invalid argument passed.\n");
		return (1);
	}
	if (*ac == 0)
	{
		free(*av);
		printf("No argument passed.\n Usage: ");
		printf("./philo nbr_philo time_to_live time_to_eat time_to_sleep\n");
		return (1);
	}
	if (*ac < 4 || *ac > 5)
	{
		printf("Too few / too much arguments.\n");
		free(*av);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				ac;
	int				*av;
	t_table			table;

	av = NULL;
	if (parse_args(argc, argv, &ac, &av))
		return (1);
	table_init(&table, ac, av);
	while (av[0]--)
	{
		if (!philo_spawn(&table, philo_routine))
		{
			philo_purge(table.philo);
			return (-1);
		}
	}
	if (table.philo && table.nbr_philo > 0)
		philo_join(&table);
	philo_purge(table.philo);
	free(av);
}
