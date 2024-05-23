#include "UbsanTester.h"

STATIC INT8 *
EFIAPI
GetelementpointerInbounds (
  INT8   *Base,
  UINTN  Offset
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
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with pointer overflow...\n\n"));

  INT8  *Base, *Result;

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 1;
  DEBUG ((
    DEBUG_WARN,
    "\nUBT: Applying non-zero offset to non-null pointer [[PTR:0x[0-9a-f]*]] produced null pointer\n",
    Base
    ));

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 2;
  DEBUG ((
    DEBUG_WARN,
    "\nUBT: Pointer index expression with base [[PTR:0x[0-9a-f]*]] overflowed to [[PTR:0x[0-9a-f]*]]\n",
    Base,
    Result
    ));

  Base   = (INT8 *)0;
  Result = Base + 0;

  DEBUG ((DEBUG_WARN, "\nUBT: Applying zero offset to null pointer\n"));

  Base   = (INT8 *)0;
  Result = Base + 1;
  DEBUG ((DEBUG_WARN, "\nUBT: Applying non-zero offset 0x1 to null pointer\n"));

  Base   = (INT8 *)1;
  Result = Base - 1;
  DEBUG ((
    DEBUG_WARN,
    "\nUBT: Applying non-zero offset to non-null pointer [[PTR:0x[0-9a-f]*]] produced null pointer\n",
    Base
    ));

  UINTN  Offset = 2ULL;

  Base    = (INT8 *)0;
  Offset -= 2;
  (VOID)GetelementpointerInbounds (Base, Offset);
  DEBUG ((DEBUG_WARN, "\nUBT: Applying zero offset to null pointer\n"));

  INT8  c;

  Base = &c;
  UINTN  NegOffset = MAX_UINTN;

  Result = Base + NegOffset;
  DEBUG ((
    DEBUG_WARN,
    "\nUBT: Addition of unsigned offset to [[PTR:0x[0-9a-f]*]] overflowed to [[PTR:0x[0-9a-f]*]]\n",
    Base,
    Result
    ));

  Result = Base - NegOffset;
  DEBUG ((
    DEBUG_WARN,
    "\nUBT: Subtraction of unsigned offset from [[PTR:0x[0-9a-f]*]] overflowed to [[PTR:0x[0-9a-f]*]]\n",
    Base,
    Result
    ));

  Base   = NULL;
  Result = Base - 1ULL;
  DEBUG ((DEBUG_WARN, "\nUBT: Applying non-zero offset 0x%lx to null pointer\n", MAX_UINTN));

  DEBUG ((DEBUG_INFO, "\n\nUBT: Checks with pointer overflow are done...\n\n"));
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
  INT32    K;
};

INT32
EFIAPI
NullCheck0 (
  INT32  *P
  )
{
  return *P;
}

INT32
EFIAPI
NullCheck1 (
  struct S  *S
  )
{
  return S->K;
}

VOID
EFIAPI
NullPointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with null pointer...\n"));
  INT32     *P = 0;
  struct S  *S = 0;

  NullCheck0 (P);
  DEBUG ((DEBUG_WARN, "\nUBT: Load of null pointer of type 'INT32' (aka 'int')\n"));

  NullCheck1 (S);
  DEBUG ((DEBUG_WARN, "\nUBT: Member access within null pointer of type 'struct S'\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with null pointer are done...\n\n\n"));
}

VOID
EFIAPI
PointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with pointers...\n"));

  PointerOverflowCheck ();
  NullPointerCheck ();

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with pointers are done...\n\n\n"));
}

