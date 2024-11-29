/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:23:41 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/29 12:47:43 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	print_message(philo, "is thinking");
}

void	take_forks(void *arg)
{
	t_philos	*philo;
	int			left_fork;
	int			right_fork;

	philo = (t_philos *)arg;
	left_fork = philo->id_philo - 1;
	right_fork = philo->id_philo % philo->data->nbr_of_philos;
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		print_message(philo, "has taken a fork");
	}
}

void	eating(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_current_time();
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->meal);
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

void	putdown_forks(void *arg)
{
	t_philos	*philo;
	int			left_fork;
	int			right_fork;

	philo = (t_philos *)arg;
	left_fork = philo->id_philo - 1;
	right_fork = philo->id_philo % philo->data->nbr_of_philos;
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void	go_sleep(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}
