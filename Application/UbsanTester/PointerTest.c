#include "UbsanTester.h"

STATIC INT8 *
EFIAPI
GetelementpointerInbounds (
  INT8    *Base,
  UINT64  Offset
  )
{
  return Base + Offset;
}

VOID
EFIAPI
PointerOverflowCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with pointer overflow...\n\n\n"));

  INT8  *Base, *Result;

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 1;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer [[PTR:0x[0-9a-f]*]] produced null pointer\n\n",
          Base
         ));

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 2;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Pointer index expression with base [[PTR:0x[0-9a-f]*]] overflowed to [[PTR:0x[0-9a-f]*]]\n\n",
          Base,
          Result
         ));

  Base   = (INT8 *)0;
  Result = Base + 0;

  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  Base   = (INT8 *)0;
  Result = Base + 1;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset 0x1 to null pointer\n\n"));

  Base   = (INT8 *)1;
  Result = Base - 1;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer [[PTR:0x[0-9a-f]*]] produced null pointer\n\n",
          Base
         ));

  UINT64  Offset = 2ULL;

  Base    = (INT8 *)0;
  Offset -= 2;
  (VOID)GetelementpointerInbounds (Base, Offset); //
  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  INT8  c;

  Base = &c;
  UINT64  NegOffset = UINT64_MAX;

  Result = Base + NegOffset;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Addition of unsigned offset to [[PTR:0x[0-9a-f]*]] overflowed to [[PTR:0x[0-9a-f]*]]\n\n",
          Base,
          Result
         ));

  Result = Base - NegOffset;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Subtraction of unsigned offset from [[PTR:0x[0-9a-f]*]] overflowed to [[PTR:0x[0-9a-f]*]]\n\n",
          Base,
          Result
         ));

  Base   = NULL;
  Result = Base - 1ULL;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset 0x%lx to null pointer\n\n", UINT64_MAX));
  

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with pointer overflow are done...\n\n\n"));
}

INT32
EFIAPI
F (
  VOID
  )
{
  return 0;
}

struct S {
  INT32    (*F)(
    VOID
    );
  INT32    k;
};

INT32
EFIAPI
NullCheck0 (
  INT32  *p
  )
{
  return *p;
}

// INT32
// EFIAPI
// NullCheck3 (
//   VOID
//   )
// {
//   INT32  q[] = { 0, 1 };

//   q[3] = 2;
//   return q[0];
// }

INT32
EFIAPI
NullCheck1 (
  struct S  *s
  )
{
  return s->k;
}

VOID 
EFIAPI
NullPointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with null pointer...\n\n"));
  INT32     *p = 0;
  struct S  *s = 0;

  NullCheck0 (p);
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'INT32' (aka 'int')\n\n"));

  NullCheck1 (s); 
  DEBUG ((DEBUG_WARN, "UBT: Member access within null pointer of type 'struct S'\n\n"));

  // NullCheck3 (); // TODO:
  // DEBUG ((DEBUG_WARN, "UBT: Index 3 is out of range for type 'INT32[2]' (aka 'int[2]')\n\n"));
  // DEBUG ((DEBUG_WARN, "UBT: Store to address [[PTR:0x[0-9a-f]*]] with insufficient space for an object of type 'INT32' (aka 'int')\n\n"));

  DEBUG ((DEBUG_INFO, "UBT: Checks with null pointer are done...\n\n\n\n\n"));
}

VOID
EFIAPI
PointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with pointers...\n"));

  PointerOverflowCheck ();
  NullPointerCheck ();

  DEBUG ((DEBUG_INFO, "UBT: Checks with pointers are done...\n\n\n\n\n"));
}
