/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:03:25 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/15 09:23:08 by ymauk            ###   ########.fr       */
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
		pthread_mutex_lock(&data->philos->meal);
		if (data->philos[i].has_eaten != data->nbr_philo_eat)
		{
			pthread_mutex_unlock(&data->philos->meal);
			return (0);
		}
		i++;
		pthread_mutex_unlock(&data->philos->meal);
	}
	return (1);
}

void	one_philo(char **argv)
{
	printf("%s 1 died\n", argv[2]);
}

int	check_mutex_var(t_philos *philo, int check)
{
	int	temp_var;

	temp_var = 0;
	if (check == 1)
	{
		pthread_mutex_lock(&philo->data->check_dead_m);
		temp_var = philo->data->check_dead;
		pthread_mutex_unlock(&philo->data->check_dead_m);
		return (temp_var);
	}
	else
		return (0);
}

void	clean_up(t_data *data)
{
	int			i;
	int			nbr_philos;

	i = 0;
	if (data->philos)
	{
		nbr_philos = data->nbr_of_philos;
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->check_dead_m);
		while (nbr_philos > i)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->philos[i].meal);
			i++;
		}
		free(data->philos);
		free(data->forks);
	}
}
