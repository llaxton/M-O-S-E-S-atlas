
#include "atList.h++"


atList::atList()
{
   // Initialize the doubly-linked list
   list_head = NULL;
   list_tail = NULL;
   num_entries = 0;

   // We haven't started traversing the list
   current_entry = NULL;
   next_entry = list_head;
}


atList::~atList()
{
   atListEntry *  current;
   atListEntry *  old;

   // Go through the list and delete the items and entries
   current = list_head;
   while (current != NULL)
   {
      // Delete the item if it exists
      if (current->item != NULL)
         delete current->item;

      // Save a pointer to this entry
      old = current;

      // Move to the next entry
      current = current->next;

      // Free the old one of which we saved a pointer
      free(old);
   }
}


u_long atList::getNumEntries()
{
   return num_entries;
}


bool atList::addEntry(atItem * item)
{
   atListEntry   *newEntry;
                                                                                
   // Create a new entry for this item in the list
   newEntry = (atListEntry *) calloc(1, sizeof(atListEntry));
   if (newEntry == NULL)
   {
      // We failed to allocate the memory so tell user and return a failure
      notify(AT_WARN, "Unable to allocate memory in List.\n");
      return false;
   }
   else
   {
      // Set the fields of the new entry
      newEntry->item = item;
      newEntry->next = NULL;
      newEntry->previous = NULL;
                                                                                
      // Add the new entry to the end of the list
      if (list_head == NULL)
      {
         // Adding only entry in list
         list_head = newEntry;
         list_tail = newEntry;
      }
      else
      {
         // Just adding it to end of list
         list_tail->next = newEntry;
         newEntry->previous = list_tail;
         list_tail = newEntry;
      }

      // Set the traversal pointers appropriately
      if (current_entry == NULL)
         next_entry = list_head;
      else
         next_entry = current_entry->next;

      // Increment the number of entries since we just added one
      num_entries++;
                                                                                
      // Return success
      return true;
   }

}


bool atList::removeCurrentEntry()
{
   atListEntry *  old;

   // If we don't have a current node, return a failure
   if (current_entry == NULL)
      return false;
   else
   {
      // Take the node out of the list (but handle special case of being
      // at the first node in the list)
      if (current_entry->previous == NULL)
      {
         // We are removing the first node so move the head pointer
         list_head = current_entry->next;

         // Now we need to fix the back pointer (previous pointer) of the
         // new first node but only if it exists of course (i.e. make sure
         // we didn't just remove the ONLY node)
         if (current_entry->next != NULL)
         {
            // We have another node so set its "previous" pointer to NULL
            // so it knows it's the front of the list
            current_entry->next->previous = NULL;
         }
         else
         {
            // We're also removing the last node (must be the only node) so
            // we need to fix the tail pointer
            list_tail = NULL;
            list_tail = NULL;
         }
      }
      else
      {
         // Otherwise, we are removing a node that isn't first so the
         // general approach works (put in the new forward link and
         // and then fix the back link if we have a node (i.e. we aren't
         // removing the last node in the list)
         current_entry->previous->next = current_entry->next;
         if (current_entry->next != NULL)
            current_entry->next->previous = current_entry->previous;
         else
         {
            // We do need to be careful with the list tail (in case we
            // removed the very last node)
            list_tail = current_entry->previous;
         }
      }

      // Save a pointer to the structure holding this item
      old = current_entry;

      // Check for head and tail issues for the "current entry"
      if (current_entry->previous == NULL)
      {
         // We removed the first node but the head is already okay; we just
         // need to do something with the "current" (so set it to NULL
         // since we don't have a previous node)
         current_entry = NULL;
         next_entry = list_head;
      }
      else if (current_entry->next == NULL)
      {
         // We removed the last node so fix the tail and set current and
         // next as being done with the list
         list_tail = current_entry->previous;
         current_entry = NULL;
         next_entry = NULL;
      }
      else
      {
         // We're removing a node in the middle so point "current" back one
         next_entry = current_entry->next;
         current_entry = current_entry->previous;
      }
                                                                                
      // Free up the structure from the list
      free(old);

      // Remove one from our counter since we just took out a node
      num_entries--;
                                                                                
      // Return success
      return true;
   }
}


bool atList::removeAllEntries()
{
   // We'll do this by calling removeCurrentEntry() for each entry in
   // the list (since we're removing all entries, it won't matter that
   // we're messing with the current_entry pointer)
   while (list_head != NULL)
   {
       current_entry = list_head;
       removeCurrentEntry();
   }

   // Set traversal pointers
   current_entry = NULL;
   next_entry = NULL;

   // Return success
   return true;
}


atItem * atList::getFirstEntry()
{
   // Go to the first node (if it exists)
   current_entry = list_head;
   if (list_head != NULL)
      next_entry = list_head->next;
   else
      next_entry = NULL;
           
   // If we have a first node, return the item stored in it
   if (current_entry != NULL)
      return current_entry->item;
   else
      return NULL;
}


atItem * atList::getNextEntry()
{
   // If there is a next node, move on and return it
   if (next_entry != NULL)
   {
      // Advance
      current_entry = next_entry;
      next_entry = current_entry->next;

      // Return the item
      return current_entry->item;
   }
   else
      return NULL;
}


atItem * atList::getPreviousEntry()
{
   // If we aren't at the beginning of the list, go to the previous node
   if (current_entry != NULL)
      current_entry = current_entry->previous;
                                                                                
   // If we have a new node, return its item
   if (current_entry != NULL)
      return current_entry->item;
   else
      return NULL;
}


atItem * atList::getNthEntry(u_long n)
{
   u_long count;

   // Walk the list until we reach the n'th element
   count = 0;
   getFirstEntry();
   while ((count < n) && (current_entry != NULL))
   {
       // Increment the count
       count++;

       // Advance the current entry pointer
       getNextEntry();
   }

   // If the current_entry is NULL (the index is greater than the number
   // of elements in the list), return NULL
   if (current_entry == NULL)
      return NULL;

   // Otherwise, return the item at the given list entry
   return current_entry->item;
}


atItem * atList::findEntry(atItem * item)
{
   atItem *currentItem;

   // Walk the list until we find an item in the list that matches the given
   // item (according to the item's equals() method)
   currentItem = getFirstEntry();
   while ((currentItem != NULL) && (!currentItem->equals(item)))
       currentItem = getNextEntry();

   // Return the item we found, or NULL if we didn't find it
   return currentItem;
}
