/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:03:25 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/02 17:28:40 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitoring;

	if (argc == 5 || argc == 6)
	{
		if (parsing(argc, argv, &data))
			return (0);
		data.start_time = get_current_time();
		// print_philos(data.philos, data.nbr_of_philos);
		create_threads(&data);
		pthread_create(&monitoring, NULL, monitoring_routine, &data);
		join_threads(&data);
		pthread_join(monitoring, NULL);
		clean_up(&data);
	}
	else
		error_handling(&data, ERROR_1);
	return (0);
}

int	all_eaten(t_data *data)
{
	int	i;

	i = 0;
	while (data->nbr_of_philos > i)
	{
		if (data->philos[i].has_eaten != data->nbr_philo_eat)
			return (0);
		i++;
	}
	return (1);
}

void	one_philo(char **argv)
{
	printf("%s 1 died\n", argv[2]);
}
