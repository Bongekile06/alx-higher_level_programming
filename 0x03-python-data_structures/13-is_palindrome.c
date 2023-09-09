#include "lists.h"

/**
 * is_palindrome - Checks if a singly linked list is a palindrome.
 * @head: Pointer to a pointer to the head of the list.
 *
 * Return: 1 if it's a palindrome, 0 otherwise.
 */
int is_palindrome(listint_t **head)
{
	listint_t *slow_ptr = *head, *fast_ptr = *head, *second_half = NULL;
	listint_t *prev_slow_ptr = *head, *mid_node = NULL;
	int is_palindrome = 1;

	if (*head == NULL || (*head)->next == NULL)
		return (1); /* Empty or single-element list is a palindrome */

	/* Use Floyd's Tortoise and Hare algorithm to find the middle of the list */
	while (fast_ptr != NULL && fast_ptr->next != NULL)
	{
		fast_ptr = fast_ptr->next->next;
		prev_slow_ptr = slow_ptr;
		slow_ptr = slow_ptr->next;
	}

	if (fast_ptr != NULL) /* Odd number of nodes, skip the middle node */
	{
		mid_node = slow_ptr;
		slow_ptr = slow_ptr->next;
	}

	/* Reverse the second half of the list */
	second_half = reverse_list(&slow_ptr);

	/* Compare the first half with the reversed second half */
	is_palindrome = compare_lists(*head, second_half);

	/* Restore the original list (if needed) */
	if (mid_node != NULL)
	{
		prev_slow_ptr->next = mid_node;
		mid_node->next = second_half;
	}
	else
	{
		prev_slow_ptr->next = second_half;
	}

	return (is_palindrome);
}

/**
 * reverse_list - Reverses a linked list.
 * @head: Pointer to a pointer to the head of the list.
 *
 * Return: Pointer to the new head of the reversed list.
 */
listint_t *reverse_list(listint_t **head)
{
	listint_t *prev = NULL, *current = *head, *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
	return (*head);
}

/**
 * compare_lists - Compares two linked lists.
 * @list1: Pointer to the head of the first list.
 * @list2: Pointer to the head of the second list.
 *
 * Return: 1 if the lists are equal, 0 otherwise.
 */
int compare_lists(listint_t *list1, listint_t *list2)
{
	while (list1 != NULL && list2 != NULL)
	{
		if (list1->n != list2->n)
			return (0); /* Not a palindrome */
		list1 = list1->next;
		list2 = list2->next;
	}
	return (list1 == NULL && list2 == NULL); /* Lists are of equal length */
}

