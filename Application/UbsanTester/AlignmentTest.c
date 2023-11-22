#include "UbsanTester.h"

INT32
F (
  VOID
  )
{
  return 0;
}

struct S {
  INT32    (*f) (
    VOID
    );
  INT32    k;
};

INT32
Check (
  INT8   Type,
  INT32  n
  )
{
  INT8      c[] __attribute__ ((aligned (8))) = { 0, 0, 0, 0, 1, 2, 3, 4, 5 };
  INT32     *p                                = (INT32 *)&c[4 + n];
  struct S  *s                                = (struct S *)p;

  (VOID)*p; // ok!
  DEBUG ((DEBUG_WARN, "UBT: Everything is fine here\n\n"));

  switch (Type) {
    case 'l':
      return *p && 0;
    case 'L':
    {
      INT32  x;
      memcpy (&x, p, sizeof (x));
      return x && 0;
    }
    case 's':
    {
      *p = 1;
      break;
    }
    case 'S':
    {
      INT32  x = 1;
      memcpy (p, &x, sizeof (x));
      break;
    }
    case 'm':
    {
      return s->k && 0;
    }
    case 'f':
    {
      s->f = F;
      return s->f () && 0;
    }
  }

  return 0;
}

VOID
AlignmentCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with alignment...\n"));
  Check ('l', 0);
  DEBUG ((DEBUG_WARN, "UBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32', which requires 4 byte alignment\n\n"));
  Check ('l', 1);
  DEBUG ((DEBUG_WARN, "UBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32', which requires 4 byte alignment\n\n"));
  Check ('L', 1); // Doesn't work
  DEBUG ((DEBUG_WARN, "UBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32 *', which requires 4 byte alignment\n\n"));
  Check ('s', 1);
  DEBUG ((DEBUG_WARN, "UBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32', which requires 4 byte alignment\n\n"));
  Check ('S', 1); // Doesn't work
  DEBUG ((DEBUG_WARN, "UBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32 *', which requires 4 byte alignment\n\n"));
  Check ('m', 1);
  DEBUG ((DEBUG_WARN, "UBT: Member access within misaligned address [[PTR:0x[0-9a-f]*]] for type 'S', which requires 4 byte alignment\n\n"));
  Check ('f', 1);
  DEBUG ((DEBUG_WARN, "UBT: Member call on misaligned address [[PTR:0x[0-9a-f]*]] for type 'S', which requires 4 byte alignment\n\n"));

  DEBUG (
         (DEBUG_INFO, "UBT: Completing testing cases with alignment...\n\n\n\n\n")
         );
}
