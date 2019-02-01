/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(this->head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
	_destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
	ListNode *node, *temp;
	node = head_;
	while (node != NULL) {
		temp = node;
		node = node->next;
		delete temp;
	}
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
	if (this->head_ == NULL) {
		ListNode *node = new ListNode(ndata);
		node->prev = NULL;
		node->next = NULL;
		this->head_ = node;
		this->tail_ = node;
	} else {
		ListNode *node = new ListNode(ndata);
		node->prev = NULL;
		node->next = this->head_;
		this->head_->prev = node;
		this->head_ = node;
	}
	this->length_ = this->length_ + 1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
	if (this->tail_ == NULL) {
		ListNode *node = new ListNode(ndata);
		node->prev = NULL;
		node->next = NULL;
		this->head_ = node;
		this->tail_ = node;
	} else {
		ListNode *node = new ListNode(ndata);
		node->prev = this->tail_;
		node->next = NULL;
		this->tail_->next = node;
		this->tail_ = node;		
	}
	this->length_ = this->length_ + 1;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
	if (startPoint == NULL || endPoint == NULL || startPoint == endPoint) {
		return;
	}

	ListNode *startprev = startPoint->prev;
	ListNode *endnext = endPoint->next;

	ListNode *startcopy = startPoint;
	ListNode *node = startPoint;
	while (node != endnext) {
		ListNode *temp = node->next;
		node->next = node->prev;
		node->prev = temp;
		node = temp;
	}
	startPoint = endPoint;
	endPoint = startcopy;

	startPoint->prev = startprev;
	if (startPoint->prev != NULL) {
		startPoint->prev->next = startPoint;
	}
	endPoint->next = endnext;
	if (endPoint->next != NULL) {
		endPoint->next->prev = endPoint;
	}
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
	/*if (n >= length_) {
		reverse(head_, tail_);
	} else {
		
		ListNode *curr1 = head_;
		ListNode *curr2 = head_;
		ListNode *rest, *subhead;
		for (int j = 0; j < n - 1; j++) {
			curr2 = curr2->next;
		}
		rest = curr2->next;
		curr2->next = NULL;
		rest->prev = NULL;

		reverse(curr1, curr2);
		head_ = curr1;
		curr2->next = rest;
		rest->prev = curr2;

		subhead = curr2;


		for (int i = n; i + n < length_; i += n) {
			curr1 = rest;
			curr2 = rest;
			for (int j = 0; j < n - 1; j++) {
				curr2 = curr2->next;
			}
			rest = curr2->next;

			curr2->next = NULL;
			rest->prev = NULL;
			subhead->next = NULL;
			curr1->prev = NULL;

			reverse(curr1, curr2);
			curr2->next = rest;
			rest->prev = curr2;
			subhead->next = curr1;
			curr1->prev = subhead;

			subhead = curr2;
		}
		curr1 = rest;
		curr2 = rest;
		while (curr2->next != NULL) {
			curr2 = curr2->next;
		}
		subhead->next = NULL;
		curr1->prev = NULL;
		reverse(curr1, curr2);
		subhead->next = curr1;
		curr1->prev = subhead;
		tail_ = curr2;
	}*/
	if (n <= 0 || n == 1) {
		return;
	} else if (n >= length_) {
		reverse(head_, tail_);
	} else {
		//cout <<"reverse n: "<< n << endl;
		//cout <<"length: "<< length_ << endl;
		ListNode *start = head_;
		ListNode *end = head_;

		int i;
        for (i = 0; i + n <= length_; i += n) {
            for (int j = 0; j < n - 1; j++) {
                end = end->next;
            }
			//cout <<"i value:"<< i << endl;
            reverse(start, end);
			if (i == 0) {
				head_ = start;
			}
            start = end->next;
            end = start;
        }

        if (start != NULL) {
            while (end->next != NULL) {
                end = end->next;
				i++;
            }
			//cout <<"last i value:"<< i << endl;
            reverse(start, end);
        }

		tail_ = end;
	}
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

    if (head_ == NULL || head_->next == NULL)
        return;

    ListNode *curr = head_;
    ListNode *temp;

    while (curr->next->next != NULL) {
        temp = curr->next;
        curr->next = temp->next;
        temp->next->prev = curr;

        temp->prev = tail_;
        temp->next = NULL;
        tail_->next = temp;
        tail_ = temp;

        curr = curr->next;
    }

}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
    ListNode *curr = start;
    int i = 0;
    while (curr != NULL && i < splitPoint) {
        curr = curr->next;
        i++;
    }

    if (curr != NULL && curr->prev != NULL) {
        curr->prev->next = NULL;
        curr->prev = NULL;
    }

    return curr;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

    ListNode *sorted;
    ListNode *sorthead;
    if (first->data < second->data) {
        sorted = first;
        first = first->next;
        sorthead = sorted;
    } else {
        sorted = second;
        second = second->next;
        sorthead = sorted;
    }

    while (first != NULL || second != NULL) {
        if (first == NULL) {
            sorted->next = second;
            second->prev = sorted;
            second = second->next;
            sorted = sorted->next;
        } else if (second == NULL) {
            sorted->next = first;
            first->prev = sorted;
            first = first->next;
            sorted = sorted->next;
        } else if (first->data < second->data) {
            sorted->next = first;
            first->prev = sorted;
            first = first->next;
            sorted = sorted->next;
        } else {
            sorted->next = second;
            second->prev = sorted;
            second = second->next;
            sorted = sorted->next;
        }
    }
    return sorthead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

    if (start->next == nullptr) {
        return start;
    }

    List<T>::ListNode *left = start;
    List<T>::ListNode *right = split(start, chainLength/2);

    int endLength;

    if (chainLength % 2 == 1) {
        endLength = chainLength / 2 + 1;
    } else {
        endLength = chainLength / 2;
    }

    List<T>::ListNode *left_half = mergesort(left, chainLength/2);
    List<T>::ListNode *right_half = mergesort(right, endLength);
    return merge(left_half, right_half);

}
