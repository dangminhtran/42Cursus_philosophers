/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:37:15 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/08 14:24:33 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_program	prog;

    if (argc < 5 || argc > 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    if (!check_args(argc, argv))
        return (1);
    if (!init_program(&prog, argc, argv))
        return (1);
    init_mutex(&prog);
    init_philos(&prog);
    init_threads(&prog);
    destroy_threads(&prog);
    destroy_mutex(&prog);
    return (0);
}


