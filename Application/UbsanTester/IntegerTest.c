#include "UbsanTester.h"

#if defined (__clang__)

VOID
EFIAPI
ShiftOutOfBoundsCheck (
  VOID
  )
{
  UINT32  P = 1;

  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with shift out of bounds...\n\n"));

  INT32  I = 32;

  P >>= I;
  DEBUG ((DEBUG_WARN, "\nUBT: Shift exponent 32 is too large for 32-bit type\n"));

  P   = 1;
  I   = -1;
  P >>= I;
  DEBUG ((DEBUG_WARN, "\nUBT: Shift exponent -1 is negative\n"));

  P   = 1;
  I   = 32;
  P <<= I;
  DEBUG ((DEBUG_WARN, "\nUBT: Shift exponent 32 is too large for 32-bit type\n"));

  P   = 1;
  I   = -1;
  P <<= I;
  DEBUG ((DEBUG_WARN, "\nUBT: Shift exponent -1 is negative\n"));

  I = 31;
  I = 1 << I;
  DEBUG ((DEBUG_WARN, "\nUBT: Left shift of 1 by 31 places cannot be represented in type 'int'\n"));

  INT32  Q = -1;

  I   = 5;
  Q <<= I;
  DEBUG ((DEBUG_WARN, "\nUBT: Left shift of negative value -1\n"));

  DEBUG ((DEBUG_INFO, "\n\nUBT: Checks with shift out of bounds are done...\n\n\n"));
}

VOID
EFIAPI
__attribute__ ((no_sanitize ("implicit-conversion")))
NegateOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with negation integer overflow...\n\n"));

  INT32  K = 0x7fffffff, N;

  N = -(UINT32)(-K - 1);
  DEBUG ((DEBUG_INFO, "\nUBT: Negation of 2147483648 cannot be represented in type 'UINT32' (aka 'unsigned int')\n"));
  N = -(-K - 1);
  DEBUG ((DEBUG_INFO, "\nUBT: Negation of -2147483648 cannot be represented in type 'int'\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with negation integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
AddOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with addition integer overflow...\n\n"));

  // These promote to 'int'.
  (VOID)((INT8)0x7f + (INT8)0x7f);
  (VOID)((INT16)0x3fff + (INT16)0x4000);

  INT32  K1 = 0x12345678;

  K1 += 0x789abcde;
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: 305419896 + 2023406814 cannot be represented in type 'int'\n"));

  INT64  K2 = (INT64)8000000000000000000LL;

  K2 += (INT64)2000000000000000000LL;
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: 8000000000000000000 + 2000000000000000000 cannot be represented in type\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with addition integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
SubOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with substraction integer overflow...\n\n"));

  // These promote to 'int'.
  (VOID)((INT8)(-2) - (INT8)0x7f);
  (VOID)((INT16)(-2) - (INT16)0x7fff);

  INT32  K1 = (-2);

  K1 -= 0x7fffffff;
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: -2 - 2147483647 cannot be represented in type 'int'\n"));

  INT64  K2 = (INT64)(-8000000000000000000LL);

  K2 -= (INT64)(2000000000000000000LL);
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: -8000000000000000000 - 2000000000000000000 cannot be represented in type\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with substraction integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
IncDecOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with increment/decrement integer overflow...\n\n"));

  INT32  N1 = 0x7ffffffd, N2 = 0x7ffffffd;

  N1++;
  N1++;
  N2++;
  N2++;
  INT32  M1 = -N1 - 1, M2 = -N2 - 1;

  ++N1;
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: 2147483647 + 1 cannot be represented in type 'int32' (aka 'int')\n"));
  N2++;
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: 2147483647 + 1 cannot be represented in type 'int32' (aka 'int')\n"));

  --M1;
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: -2147483648 - 1 cannot be represented in type 'int32' (aka 'int')\n"));
  M2--;
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: -2147483648 - 1 cannot be represented in type 'int32' (aka 'int')\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with increment/decrement integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
MulOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with multiplication integer overflow...\n\n"));

  // These promote to 'int'.
  INT32  K;

  K = ((INT8)-2 * (INT8)0x7f);
  K = ((INT16)0x7fff * (INT16)0x7fff);
  K = ((UINT16)0xffff * (INT16)0x7fff);
  K = ((UINT16)0xffff * (UINT16)0x8000);

  UINT16  M1 = 0xffff, M2 = 0x8001;

  (VOID)(M1 * M2);
  DEBUG ((DEBUG_INFO, "\nUBT: Signed integer overflow: 65535 * 32769 cannot be represented in type 'int'\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with multiplication integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
UnsignedAddOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with unsigned addition integer overflow...\n\n"));

  // These promote to 'int'.
  (VOID)((UINT8)0xff + (UINT8)0xff);
  (VOID)((UINT16)0x0fff + (UINT16)0xf0fff);

  UINT32  K1 = 0x87654321;

  K1 += 0xedcba987;
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 2271560481 + 3989547399 cannot be represented in type 'unsigned int'\n"));

  UINT64  K2 = (UINT64)10000000000000000000ULL;

  K2 += (UINT64)9000000000000000000ULL;
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 10000000000000000000 + 9000000000000000000 cannot be represented in type\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with unsigned addition integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
UnsignedSubOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with unsigned substraction integer overflow...\n\n"));

  // These promote to 'int'.
  (VOID)((UINT8)(0) - (UINT8)0x7f);
  (VOID)((UINT16)(0) - (UINT16)0x7fff);

  UINT32  K1 = 1;

  K1 -= 2;
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 1 - 2 cannot be represented in type\n"));

  UINT64  K2 = (UINT64)(8000000000000000000ULL);

  K2 -= (UINT64)(9000000000000000000ULL);
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 8000000000000000000 - 9000000000000000000 cannot be represented in type\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with unsigned substraction integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
UnsignedIncDecOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with unsigned increment/decrement integer overflow...\n\n"));

  UINT32  N1 = 0xfffffffd, N2 = 0xfffffffd;

  N1++;
  N1++;
  N2++;
  N2++;
  UINT32  M1 = 0, M2 = 0;

  ++N1;
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 4294967295 + 1 cannot be represented in type 'UINT32' (aka 'unsigned int')\n"));
  N2++;
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 4294967295 + 1 cannot be represented in type 'UINT32' (aka 'unsigned int')\n"));

  --M1;
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 0 - 1 cannot be represented in type 'UINT32' (aka 'unsigned int')\n"));
  M2--;
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 0 - 1 cannot be represented in type 'UINT32' (aka 'unsigned int')\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with unsigned increment/decrement integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
__attribute__ ((no_sanitize ("signed-integer-overflow")))
UnsignedMulOverflow (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with multiplication integer overflow...\n\n"));

  // These promote to 'int'.
  INT32  K;

  K = ((INT8)-2 * (INT8)0x7f);
  K = ((INT16)0x7fff * (INT16)0x7fff);
  K = ((UINT16)0xffff * (INT16)0x7fff);
  K = ((UINT16)0xffff * (UINT16)0x8000);

  UINT16  M1 = 0xffff, M2 = 0x8001;

  (VOID)(M1 * M2);

  UINT32  M3 = 0xffffffff, M4 = 0x2;

  (VOID)(M3 * M4);
  DEBUG ((DEBUG_INFO, "\nUBT: Unsigned integer overflow: 4294967295 * 2 cannot be represented in type\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with multiplication integer overflow are done...\n\n\n"));
}

VOID
EFIAPI
IntegerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with integer...\n\n"));

  ShiftOutOfBoundsCheck ();
  NegateOverflow ();

  AddOverflow ();
  SubOverflow ();
  IncDecOverflow ();
  MulOverflow ();

  UnsignedAddOverflow ();
  UnsignedSubOverflow ();
  UnsignedIncDecOverflow ();
  UnsignedMulOverflow ();
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with integer are done...\n\n\n"));
}

#endif
