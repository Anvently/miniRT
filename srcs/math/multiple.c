/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:05:28 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 14:34:27 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_inf_multiple(int n, int comp)
{
	int	i;

	i = comp - 1;
	if (i == 0)
		return (1);
	while (i > 1)
	{
		if (n % i == 0)
			return (i);
		i--;
	}
	return (i);
}

int	get_sup_multiple(int n, int comp, int max)
{
	int	i;

	i = comp + 1;
	while (i < max && i < n)
	{
		if (n % i == 0)
			return (i);
		i++;
	}
	if (i == max || i == n)
	{
		if (n % comp == 0)
			return (comp);
		else
			return (get_inf_multiple(n, comp));
	}
	return (0);
}
