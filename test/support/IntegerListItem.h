#ifndef INTEGERLISTITEM_H
#define INTEGERLISTITEM_H

#include <stdlib.h>
#include "ListItem.h"


typedef	struct	IntegerListItem	IntegerListItem;
struct IntegerListItem{
	ListItem		*next;
	ListItem		*prev;
	uintptr_t			data;
};

typedef struct{
  int val1;
  double  val2;
}Data;

#endif // INTEGERLISTITEM_H
