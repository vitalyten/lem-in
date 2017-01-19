/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:07:00 by vtenigin          #+#    #+#             */
/*   Updated: 2017/01/18 17:19:53 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	getnba(t_en *env)
{
	if (get_next_line(0, &env->str) < 1)
		showerr();
	if (!ft_isnumber(env->str))
		showerr();
	env->nba = ft_atoi(env->str);
	if (env->nba < 1)
		showerr();
	ft_printf("%d\n", env->nba);
	ft_strdel(&env->str);
}

void	envinit(t_en *env)
{
	env->start = 0;
	env->end = 0;
	env->nbr = 0;
}

void	checkmap(t_room *room)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (room)
	{
		if (room->start)
			start++;
		if (room->end)
			end++;
		room = room->next;
	}
	if (start != 1 || end != 1)
		showerr();
}



int	main(void) // add check for start and end
{
	t_en	env;
	t_room	*room;
	t_link	*link;

	room = NULL;
	envinit(&env);
	getnba(&env);
	room = readroom(&env);
	readlinks(&env, room);
	checkmap(room);
	setdtoe(room);
	while (room)
	{
		ft_printf("name = %s start = %d end = %d dtoe = %d\n",
			room->name, room->start, room->end, room->dtoe);
		link = room->link;
		while (link)
		{
			ft_printf("link : name = %s\n", link->room->name);
			link = link->next;
		}
		room = room->next;
	}
}

void		showerr(void)
{
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

int			ft_isnumber(char *n)
{
	int i;

	i = 0;
	if (n[0] == '-' || n[0] == '+')
		i++;
	while (n[i])
		if (!ft_isdigit(n[i++]))
			return (0);
	return (1);
}

// long long	ft_atoll(const char *str)
// {
// 	long long	res;
// 	long long	sign;

// 	res = 0;
// 	sign = 1;
// 	while (ft_iswhitespace(*str))
// 		str++;
// 	if (*str == '-')
// 	{
// 		sign = -1;
// 		str++;
// 	}
// 	else if (*str == '+')
// 		str++;
// 	while (ft_isdigit(*str))
// 	{
// 		res = res * 10 + *str - '0';
// 		str++;
// 	}
// 	return (sign * res);
// }



// void	free2d(char **strs)
// {
// 	int i;

// 	i = -1;
// 	while (strs[++i])
// 		free(strs[i]);
// 	free(strs);
// }
