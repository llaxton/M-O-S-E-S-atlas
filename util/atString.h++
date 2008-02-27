
#ifndef AT_STRING_H
#define AT_STRING_H


// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "atItem.h++"


class atString : public atItem
{
   protected:
      char *   local_string;
      int      string_length;

   public:
      atString();
      atString(char * stringToCopy);
      atString(char * stringToCopy, u_long maxLength);
      atString(const atString & stringToCopy);
      virtual ~atString();

      virtual atString       clone();

      virtual void           append(const atString & stringToAppend);
      virtual atString       concat(const atString & stringToConcat) const;

      virtual void           setString(const char * stringToCopy);
      virtual void           setString(const char * stringToCopy, 
                                       u_long maxLength);
      virtual void           setString(const atString & stringToCopy);

      virtual const char *   getString() const;
      virtual char *         getString();

      virtual char           getCharAt(int index);
      virtual int            getLength();

      virtual bool           equals(atItem * otherItem);
      virtual int            compare(atItem * otherItem);

      virtual void           operator=(atString stringToCopy);
};

#endif

