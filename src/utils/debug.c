#include "../../include/minishell.h"

void	debug_list(t_list *head)
{
	t_list *current = head;

	while (current)
	{
		printf("Node at %p:\n", (void *)current);
		printf("  data  : \"%s\"\n", current->data ? current->data : "(null)");
		printf("  type  : %d\n", current->type);
		printf("  prev  : %p\n", (void *)current->prev);
		printf("  next  : %p\n", (void *)current->next);
		printf("--------\n");
		current = current->next;
	}
}

