/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 23:20:07 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/23 17:56:42 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*new_elem;

	if (!lst)
		return (NULL);
	if (!(lst_new = ft_lstnew((*f)(lst->content))))
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new_elem = ft_lstnew((*f)(lst->content));
		if (!new_elem)
			ft_lstclear(&lst_new, del);
		ft_lstadd_back(&lst_new, new_elem);
		lst = lst->next;
	}
	return (lst_new);
}
