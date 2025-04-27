/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:03:25 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/27 16:34:13 by ymauk            ###   ########.fr       */
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
	pthread_mutex_lock(&data->philos->meal);
	if (data->nbr_philo_eat == -1)
	{
		pthread_mutex_unlock(&data->philos->meal);
		return (0);
	}
	pthread_mutex_unlock(&data->philos->meal);
	while (data->nbr_of_philos > i)
	{
		pthread_mutex_lock(&data->philos->meal);
		if (data->philos[i].has_eaten < data->nbr_philo_eat)
		{
			pthread_mutex_unlock(&data->philos->meal);
			return (0);
		}
		i++;
		pthread_mutex_unlock(&data->philos->meal);
	}
	usleep(500);
	data->check_snacks = 1;
	return (1);
}

void	one_philo(void *arg)
{
	t_philos	*philo;
	int			left_fork;

	philo = arg;
	left_fork = philo->id_philo - 1;
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	print_message(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
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
	else if (check == 2)
	{
		pthread_mutex_lock(&philo->data->snacks_m);
		temp_var = philo->data->check_snacks;
		pthread_mutex_unlock(&philo->data->snacks_m);
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
		pthread_mutex_destroy(&data->snacks_m);
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
