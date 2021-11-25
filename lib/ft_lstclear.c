/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:19:36 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/23 21:01:24 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list2;
	t_list	*list3;

	list2 = *lst;
	list3 = *lst;
	while (list3)
	{
		list3 = list3->next;
		ft_lstdelone(list2, del);
		list2 = list3;
	}
	*lst = NULL;
}
