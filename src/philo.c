/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:03:25 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/22 17:06:05 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 1)
	{
		parsing(argc, argv, &data);
		print_philos(data.philos, data.nbr_of_philos);
		create_threads(&data);
		join_threads(&data);

	}
	return (0);
}

void	print_philos(t_philos *head, int nbr_of_philos)
{
    t_philos *current = head;
    int count = 0;

    if (!current)
    {
        printf("Die Liste ist leer.\n");
        return;
    }

    printf("Philosophenliste:\n");
    do
    {
        printf("Philosoph ID: %d\n", current->id_philo);
        current = current->next;
        count++;
    } while (current && count < nbr_of_philos); // Abbruch nach der Anzahl der Philosophen

    // Hinweis auf Zirkularität
    if (count == nbr_of_philos && current == head)
        printf("Die Liste ist zirkulär.\n");
    else
        printf("Die Liste ist nicht vollständig zirkulär.\n");
}
