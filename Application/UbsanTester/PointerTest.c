#include "UbsanTester.h"

STATIC INT8 *
getelementpointerInbounds (
  INT8    *base,
  UINT64  offset
  )
{
  return base + offset;
}

VOID
pointerOverflowCheck (
  VOID
  )
{
  // mb need to separate code

  DEBUG ((DEBUG_WARN, "UBT: Pointer overflow\n\n\n"));

  INT8  *base, *result;

  base   = (INT8 *)MAX_ADDRESS;
  result = base + 1;
  DEBUG (
         (DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer 0x%X produced null "
          "pointer\n\n",
          base)
         );

  base   = (INT8 *)MAX_ADDRESS;
  result = base + 2;
  DEBUG (
         (DEBUG_WARN,
          "UBT: Addition of unsigned offset from 0x%X overflowed to 0x%X\n\n",
          base, result)
         );

  base   = (INT8 *)0;
  result = base + 0;

  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  base   = (INT8 *)0;
  result = base + 1;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset 1 to null pointer\n\n"));

  base   = (INT8 *)1;
  result = base - 1;
  DEBUG (
         (DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer 0x%X produced null "
          "pointer\n\n",
          base)
         );

  UINT64  offset = 2ULL;

  base    = (INT8 *)0;
  offset -= -1;
  (VOID)getelementpointerInbounds (base, offset);
  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  INT8  c;

  base = &c;
  INT64  negOffset = -1;

  result = base + negOffset;  // doesn't work
  DEBUG (
         (DEBUG_WARN,
          "UBT: Addition of unsigned offset to 0x%X overflowed to 0x%X\n\n",
          base, result)
         );

  result = base - negOffset;  // doesn't work
  DEBUG (
         (DEBUG_WARN,
          "UBT: Subtraction of unsigned offset from 0x%X overflowed to 0x%X\n\n",
          base, result)
         );

  base   = NULL;
  result = base - 1ULL;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset -1 to null pointer\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Pointer overflow checks are done.\n\n\n"));
}

INT32
f (
  VOID
  )
{
  return 0;
}

struct S {
  INT32    (*f)(
    VOID
    );
  INT32    k;
};

INT32
nullCheck0 (
  INT32  *p
  )
{
  return *p;
}

INT32
nullCheck3 (
  VOID
  )
{
  INT32  q[] = { 0, 1 };

  q[3] = 2;
  return q[0];
}

/*
  INT32* check_2 (INT32** p) {
      INT32 *r;
      r = *p;
      return r;
  }
*/
INT32
nullCheck1 (
  struct S  *s
  )
{
  return s->k;
}

VOID
nullPointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_WARN, "UBT: Null pointer...\n\n"));
  INT32     *p = 0;
  struct S  *s = 0;

  (VOID)*p;  // ok!
  DEBUG ((DEBUG_WARN, "UBT: Everything is fine here\n\n"));

  nullCheck0 (p);
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'INT32'\n\n"));

  nullCheck1 (s);
  DEBUG ((DEBUG_WARN, "UBT: Member access within null pointer of type 'S'\n\n"));

  /*
    check_2(q); Only in c++?
    DEBUG ((DEBUG_WARN, "UBT: Reference binding to null pointer of type
    'INT32'\n\n"));
  */

  nullCheck3 ();  // It works, but throws assert /:
  // *p = 1;
  DEBUG ((DEBUG_WARN, "UBT: Store to null pointer of type 'INT32'\n\n"));

  DEBUG ((DEBUG_INFO, "UBT: Checks with null pointer are done.\n\n\n\n\n"));
}

VOID
pointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with pointers...\n"));

  pointerOverflowCheck ();

  nullPointerCheck ();

  DEBUG (
         (DEBUG_INFO, "UBT: Completing testing cases with pointers...\n\n\n\n\n")
         );
}
