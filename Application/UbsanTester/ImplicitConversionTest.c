#include "UbsanTester.h"

/*
 * Implicit conversion group of checks.
 *
 * Enables implicit-unsigned-integer-truncation, implicit-signed-integer-truncation,
 * and implicit-integer-sign-change.
 *
 * Use -fsanitize=implicit-conversion
 */
UINT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedIntToUnsignedInt (
  UINT32  x
  )
{
  #line 100
  return x;
}

UINT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedCharToUnsignedChar (
  UINT8  x
  )
{
  #line 200
  return x;
}

INT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedIntToSignedInt (
  INT32  x
  )
{
  #line 300
  return x;
}

INT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedCharToSignedChar (
  INT8  x
  )
{
  #line 400
  return x;
}

UINT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedIntToUnsignedChar (
  UINT32  x
  )
{
  #line 500
  return x;
}

UINT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedCharToUnsignedInt (
  UINT8  x
  )
{
  #line 600
  return x;
}

INT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedCharToSignedInt (
  UINT8  x
  )
{
  #line 700
  return x;
}

INT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedCharToSignedInt (
  INT8  x
  )
{
  #line 800
  return x;
}

INT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedIntToSignedInt (
  UINT32  x
  )
{
  #line 900
  return x;
}

UINT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedIntToUnsignedInt (
  INT32  x
  )
{
  #line 1000
  return x;
}

UINT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedIntToUnsignedChar (
  INT32  x
  )
{
  #line 1100
  return x;
}

UINT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedCharToUnsignedChar (
  INT8  x
  )
{
  #line 1200
  return x;
}

INT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedCharToSignedChar (
  UINT8  x
  )
{
  #line 1300
  return x;
}

UINT32
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedCharToUnsignedInt (
  INT8  x
  )
{
  #line 1400
  return x;
}

INT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertUnsignedIntToSignedChar (
  UINT32  x
  )
{
  #line 1500
  return x;
}

INT8
EFIAPI
__attribute__((no_sanitize("undefined")))
ConvertSignedIntToSignedChar (
  INT32  x
  )
{
  #line 1600
  return x;
}

VOID
EFIAPI
__attribute__((no_sanitize("undefined")))
TestUnsignedIncdec (
  VOID
  )
{
  UINT8  x;

  x = 0;
  x++;
  x = 0;
  ++x;

  x = 0;
  x--;
  // integer-conversion-incdec: implicit conversion from type 'int' of value -1 (32-bit, signed) to type 'unsigned char' changed the value to 255 (8-bit, unsigned)
  // integer-sign-change-incdec
  x = 0;
  --x;
  // integer-conversion-incdec: implicit conversion from type 'int' of value -1 (32-bit, signed) to type 'unsigned char' changed the value to 255 (8-bit, unsigned)
  // integer-sign-change-incdec

  x = 1;
  x++;
  x = 1;
  ++x;

  x = 1;
  x--;
  x = 1;
  --x;

  x = 254;
  x++;
  x = 254;
  ++x;

  x = 254;
  x--;
  x = 254;
  --x;

  x = 255;
  x++;
  // integer-conversion-incdec: runtime error: implicit conversion from type 'int' of value 256 (32-bit, signed) to type 'unsigned char' changed the value to 0 (8-bit, unsigned)
  x = 255;
  ++x;
  // integer-conversion-incdec: implicit conversion from type 'int' of value 256 (32-bit, signed) to type 'unsigned char' changed the value to 0 (8-bit, unsigned)

  x = 255;
  x--;
  x = 255;
  --x;
}

VOID
EFIAPI
__attribute__((no_sanitize("undefined")))
TestSignedIncdec (
  VOID
  )
{
  INT8  x;

  x = -128;
  x++;
  x = -128;
  ++x;

  x = -128;
  x--;
  // integer-conversion-incdec: implicit conversion from type 'int' of value -129 (32-bit, signed) to type 'signed char' changed the value to 127 (8-bit, signed)
  // integer-sign-change-incdec
  x = -128;
  --x;
  // integer-conversion-incdec: implicit conversion from type 'int' of value -129 (32-bit, signed) to type 'signed char' changed the value to 127 (8-bit, signed)
  // integer-sign-change-incdec

  x = -1;
  x++;
  x = -1;
  ++x;

  x = -1;
  x--;
  x = -1;
  --x;

  x = 0;
  x++;
  x = 0;
  ++x;

  x = 0;
  x--;
  x = 0;
  --x;

  x = 1;
  x++;
  x = 1;
  ++x;

  x = 1;
  x--;
  x = 1;
  --x;

  x = 127;
  x++;
  // integer-conversion-incdec: implicit conversion from type 'int' of value 128 (32-bit, signed) to type 'signed char' changed the value to -128 (8-bit, signed)
  // integer-sign-change-incdec
  x = 127;
  ++x;
  // integer-conversion-incdec: implicit conversion from type 'int' of value 128 (32-bit, signed) to type 'signed char' changed the value to -128 (8-bit, signed)
  // integer-sign-change-incdec

  x = 127;
  x--;
  x = 127;
  --x;
}

VOID
EFIAPI
__attribute__((no_sanitize("undefined")))
CheckIncDec (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with integer conversion inc dec...\n\n"));
  TestSignedIncdec ();
  TestUnsignedIncdec ();
  DEBUG ((DEBUG_INFO, "UBT: Checks with  integer conversion inc dec are done...\n\n\n\n\n"));
}

VOID
EFIAPI
__attribute__((no_sanitize("undefined")))
CheckIntegerOverflowWithAbs (
  VOID
  )
{
  // TODO:
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with integer overflow with abs...\n\n"));
  INT32  P;

  P = __builtin_abs (INT32_MIN);

  INT64  Q;

  Q = __builtin_labs (INT64_MIN);
  Q = __builtin_llabs (INT64_MIN);

  DEBUG ((DEBUG_INFO, "UBT: Checks with integer overflow with abs are done...\n\n\n\n\n"));
}

VOID
EFIAPI
__attribute__((no_sanitize("undefined")))
ShiftOutOfBoundsCheck (
  VOID
  )
{
  UINT16  p = 1;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with shift out of bounds...\n\n\n"));

  INT32  i = 32;

  p >>= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent 32 is too large for 16-bit type\n\n"));

  p   = 1;
  i   = -1;
  p >>= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent -1 is negative\n\n"));

  p   = 1;
  i   = 32;
  p <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent 32 is too large for 16-bit type\n\n"));

  p   = 1;
  i   = -1;
  p <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent -1 is negative\n\n"));

  i = 31;
  i = 1 << i;
  DEBUG ((DEBUG_WARN, "UBT: Left shift of 1 by 31 places cannot be represented in 32-bit type \n\n"));

  INT32  q = -1;

  i   = 5;
  q <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Left shift of negative value -1\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with shift out of bounds are done...\n\n\n\n\n"));
}

// TODO: mb need to separate the cases
VOID
EFIAPI
__attribute__((no_sanitize("undefined")))
CheckConvertArithmeticsValue (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with integer..."));

  // CheckIntegerOverflowWithAbs ();

  CheckIncDec ();

  // All source bits set.
  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when all source bits set\n"));

  /* For -fsanitize=implicit-conversion
     ubsan have no check 500, 900-1500

     For -fsanitize=implicit-integer-truncation
      500, 1100
  */

  ConvertUnsignedIntToUnsignedInt ((UINT32)UINT32_MAX);
  ConvertUnsignedCharToUnsignedChar ((UINT8)UINT8_MAX);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)UINT32_MAX);
  ConvertSignedCharToSignedChar ((INT8)UINT8_MAX);
  ConvertUnsignedIntToUnsignedChar ((UINT32)UINT32_MAX);
  ConvertUnsignedCharToUnsignedInt ((UINT8)UINT8_MAX);
  ConvertUnsignedCharToSignedInt ((UINT8)UINT8_MAX);
  ConvertSignedCharToSignedInt ((INT8)UINT8_MAX);
  ConvertUnsignedIntToSignedInt ((UINT32)UINT32_MAX);
  // 900: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 4294967295 (32-bit, unsigned) to type '{{.*}}' (aka 'int') changed the value to -1 (32-bit, signed)
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)UINT32_MAX);
  // 1000: implicit conversion from type '{{.*}}' (aka 'int') of value -1 (32-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967295 (32-bit, unsigned)
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)UINT32_MAX);
  // 1100: implicit conversion from type '{{.*}}' (aka 'int') of value -1 (32-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 255 (8-bit, unsigned)
  ConvertSignedCharToUnsignedChar ((INT8)UINT8_MAX);
  // 1200: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -1 (8-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 255 (8-bit, unsigned)
  ConvertUnsignedCharToSignedChar ((UINT8)UINT8_MAX);
  // 1300: implicit conversion from type '{{.*}}' (aka 'unsigned char') of value 255 (8-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -1 (8-bit, signed)
  ConvertSignedCharToUnsignedInt ((INT8)UINT8_MAX);
  // 1400:implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -1 (8-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967295 (32-bit, unsigned)
  ConvertUnsignedIntToSignedChar ((UINT32)UINT32_MAX);
  // 1500:implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 4294967295 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -1 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32)(UINT32)UINT32_MAX);
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  // Source 'Sign' bit set.

  // !!! The last doesn't work at integer-arithmetic-value-change
  // !!! The last doesn't work at implicit-conversion
  // !!! The last second doesn't work at implicit-integer-truncation
  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when source \'Sign\' bit is set...\n"));

  /* For -fsanitize=implicit-conversion
     ubsan have no check 500, 900-1600

     For -fsanitize=implicit-integer-truncation
     500, 1100, 1500, 1600
  */

  ConvertUnsignedIntToUnsignedInt ((UINT32)INT32_MIN);
  ConvertUnsignedCharToUnsignedChar ((UINT8)INT8_MIN);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)INT32_MIN);
  ConvertSignedCharToSignedChar ((INT8)INT8_MIN);
  ConvertUnsignedIntToUnsignedChar ((UINT32)INT32_MIN);
  ConvertUnsignedCharToUnsignedInt ((UINT8)INT8_MIN);
  ConvertUnsignedCharToSignedInt ((UINT8)INT8_MIN);
  ConvertSignedCharToSignedInt ((INT8)INT8_MIN);
  ConvertUnsignedIntToSignedInt ((UINT32)INT32_MIN);
  // 900: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 2147483648 (32-bit, unsigned) to type '{{.*}}' (aka 'int') changed the value to -2147483648 (32-bit, signed)
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)INT32_MIN);
  // 1000: implicit conversion from type '{{.*}}' (aka 'int') of value -2147483648 (32-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 2147483648 (32-bit, unsigned)
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)INT32_MIN);
  // 1100: implicit conversion from type '{{.*}}' (aka 'int') of value -2147483648 (32-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 0 (8-bit, unsigned)
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MIN);
  // 1200: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 128 (8-bit, unsigned)
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MIN);
  // 1300: implicit conversion from type '{{.*}}' (aka 'unsigned char') of value 128 (8-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MIN);
  // 1400: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967168 (32-bit, unsigned)
  ConvertUnsignedIntToSignedChar ((UINT32)INT32_MIN);
  // 1500: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 2147483648 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to 0 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32)(UINT32)INT32_MIN);
  // 1600: implicit conversion from type '{{.*}}' (aka 'int') of value -2147483648 (32-bit, signed) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to 0 (8-bit, signed)
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  // All bits except the source 'Sign' bit are set.
  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when all bits except the source \'Sign\' bit are set...\n"));

  /* For -fsanitize=implicit-conversion
     ubsan have no check 500, 1100, 1500, 1600

     For -fsanitize=implicit-integer-truncation
     500, 1100, 1500, 1600
  */

  ConvertUnsignedIntToUnsignedInt ((UINT32)INT32_MAX);
  ConvertUnsignedCharToUnsignedChar ((UINT8)INT8_MAX);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)INT32_MAX);
  ConvertSignedCharToSignedChar ((INT8)INT8_MAX);
  ConvertUnsignedIntToUnsignedChar ((UINT32)INT32_MAX);
  ConvertUnsignedCharToUnsignedInt ((UINT8)INT8_MAX);
  ConvertUnsignedCharToSignedInt ((UINT8)INT8_MAX);
  ConvertSignedCharToSignedInt ((INT8)INT8_MAX);
  ConvertUnsignedIntToSignedInt ((UINT32)INT32_MAX);
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)INT32_MAX);
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)INT32_MAX);
  // 1100: implicit conversion from type '{{.*}}' (aka 'int') of value 2147483647 (32-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 255 (8-bit, unsigned)
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MAX);
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MAX);
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MAX);
  ConvertUnsignedIntToSignedChar ((UINT32)INT32_MAX);
  // 1500: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 2147483647 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -1 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32)(UINT32)INT32_MAX);
  // 1600: implicit conversion from type '{{.*}}' (aka 'int') of value 2147483647 (32-bit, signed) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -1 (8-bit, signed)
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  // All destination bits set.

  /* For -fsanitize=implicit-conversion
     ubsan have no check 1200-1600

     For -fsanitize=implicit-integer-truncation
     1500, 1600
  */

  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when all destination bits are set...\n"));

  ConvertUnsignedIntToUnsignedInt ((UINT32)UINT8_MAX);
  ConvertUnsignedCharToUnsignedChar ((UINT8)UINT8_MAX);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)UINT8_MAX);
  ConvertSignedCharToSignedChar ((INT8)UINT8_MAX);
  ConvertUnsignedIntToUnsignedChar ((UINT32)UINT8_MAX);
  ConvertUnsignedCharToUnsignedInt ((UINT8)UINT8_MAX);
  ConvertUnsignedCharToSignedInt ((UINT8)UINT8_MAX);
  ConvertSignedCharToSignedInt ((INT8)UINT8_MAX);
  ConvertUnsignedIntToSignedInt ((UINT32)UINT8_MAX);
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)UINT8_MAX);
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)UINT8_MAX);
  ConvertSignedCharToUnsignedChar ((INT8)UINT8_MAX);
  // 1200: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -1 (8-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 255 (8-bit, unsigned)
  ConvertUnsignedCharToSignedChar ((UINT8)UINT8_MAX);
  // 1300: implicit conversion from type '{{.*}}' (aka 'unsigned char') of value 255 (8-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -1 (8-bit, signed)
  ConvertSignedCharToUnsignedInt ((INT8)UINT8_MAX);
  // 1400: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -1 (8-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967295 (32-bit, unsigned)
  ConvertUnsignedIntToSignedChar ((UINT32)UINT8_MAX);
  // 1500: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 255 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -1 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32)(UINT32)UINT8_MAX);
  // 1600: implicit conversion from type '{{.*}}' (aka 'int') of value 255 (32-bit, signed) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -1 (8-bit, signed)
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  // Destination 'sign' bit set.

  /* For -fsanitize=implicit-conversion
     ubsan have no check 1200-1600

     For -fsanitize=implicit-integer-truncation
     1500, 1600
  */

  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when destination \'Sign\' bit is set...\n"));

  ConvertUnsignedIntToUnsignedInt ((UINT32)(UINT8)INT8_MIN);
  ConvertUnsignedCharToUnsignedChar ((UINT8)(UINT8)INT8_MIN);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)(UINT8)INT8_MIN);
  ConvertSignedCharToSignedChar ((INT8)(UINT8)INT8_MIN);
  ConvertUnsignedIntToUnsignedChar ((UINT32)(UINT8)INT8_MIN);
  ConvertUnsignedCharToUnsignedInt ((UINT8)(UINT8)INT8_MIN);
  ConvertUnsignedCharToSignedInt ((UINT8)(UINT8)INT8_MIN);
  ConvertSignedCharToSignedInt ((INT8)(UINT8)INT8_MIN);
  ConvertUnsignedIntToSignedInt ((UINT32)(UINT8)INT8_MIN);
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)(UINT8)INT8_MIN);
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)(UINT8)INT8_MIN);
  ConvertSignedCharToUnsignedChar ((INT8)(UINT8)INT8_MIN);
  // 1200: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 128 (8-bit, unsigned)
  ConvertUnsignedCharToSignedChar ((UINT8)(UINT8)INT8_MIN);
  // 1300: implicit conversion from type '{{.*}}' (aka 'unsigned char') of value 128 (8-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  ConvertSignedCharToUnsignedInt ((INT8)(UINT8)INT8_MIN);
  // 1400: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967168 (32-bit, unsigned)
  ConvertUnsignedIntToSignedChar ((UINT32)(UINT8)INT8_MIN);
  // 1500: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 128 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32)(UINT32)(UINT8)INT8_MIN);
  // 1600: implicit conversion from type '{{.*}}' (aka 'int') of value 128 (32-bit, signed) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  // All bits except the destination 'sign' bit are set.

  /* For -fsanitize=implicit-conversion
     ubsan have no check 500, 900-1600

     For -fsanitize=implicit-integer-truncation
     500, 1100, 1500, 1600
  */

  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when all bits except the destination \'Sign\' bit are set...\n"));

  ConvertUnsignedIntToUnsignedInt ((~((UINT32)(UINT8)INT8_MIN)));
  ConvertUnsignedCharToUnsignedChar ((UINT8)(UINT8)INT8_MIN);
  ConvertSignedIntToSignedInt ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  ConvertSignedCharToSignedChar ((INT8)(UINT8)INT8_MIN);
  ConvertUnsignedIntToUnsignedChar ((~((UINT32)(UINT8)INT8_MIN)));
  ConvertUnsignedCharToUnsignedInt ((UINT8)(UINT8)INT8_MIN);
  ConvertUnsignedCharToSignedInt ((UINT8)(UINT8)INT8_MIN);
  ConvertSignedCharToSignedInt ((INT8)(UINT8)INT8_MIN);
  ConvertUnsignedIntToSignedInt ((~((UINT32)(UINT8)INT8_MIN)));
  // 900: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 4294967167 (32-bit, unsigned) to type '{{.*}}' (aka 'int') changed the value to -129 (32-bit, signed)
  ConvertSignedIntToUnsignedInt ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  // 1000:implicit conversion from type '{{.*}}' (aka 'int') of value -129 (32-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967167 (32-bit, unsigned)
  ConvertSignedIntToUnsignedChar ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  // 1100: implicit conversion from type '{{.*}}' (aka 'int') of value -129 (32-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 127 (8-bit, unsigned)
  ConvertSignedCharToUnsignedChar ((INT8)(UINT8)INT8_MIN);
  // 1200: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 128 (8-bit, unsigned)
  ConvertUnsignedCharToSignedChar ((UINT8)(UINT8)INT8_MIN);
  // 1300: implicit conversion from type '{{.*}}' (aka 'unsigned char') of value 128 (8-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  ConvertSignedCharToUnsignedInt ((INT8)(UINT8)INT8_MIN);
  // 1400: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967168 (32-bit, unsigned)
  ConvertUnsignedIntToSignedChar ((~((UINT32)(UINT8)INT8_MIN)));
  // 1500: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 4294967167 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to 127 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  // 1600: implicit conversion from type '{{.*}}' (aka 'int') of value -129 (32-bit, signed) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to 127 (8-bit, signed)
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  // Only the source and destination sign bits are set.

  /* For -fsanitize=implicit-conversion
     ubsan have no check 500, 900-1600

     For -fsanitize=implicit-integer-truncation
     500, 1100, 1500, 1600
  */

  // !!! The last doesn't work at integer-arithmetic-value-change
  // !!! The last doesn't work at implicit-conversion
  // !!! The last second doesn't work at implicit-integer-truncation

  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when only the source and destination \'Sign\' bits are set...\n"));

  ConvertUnsignedIntToUnsignedInt ((UINT32)INT32_MIN);
  ConvertUnsignedCharToUnsignedChar ((UINT8)INT8_MIN);
  ConvertSignedIntToSignedInt ((INT32)INT32_MIN);
  ConvertSignedCharToSignedChar ((INT8)INT8_MIN);
  ConvertUnsignedIntToUnsignedChar (((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN));
  ConvertUnsignedCharToUnsignedInt ((UINT8)INT8_MIN);
  ConvertUnsignedCharToSignedInt ((UINT8)INT8_MIN);
  ConvertSignedCharToSignedInt ((INT8)INT8_MIN);
  ConvertUnsignedIntToSignedInt ((UINT32)INT32_MIN);
  // 900: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 2147483648 (32-bit, unsigned) to type '{{.*}}' (aka 'int') changed the value to -2147483648 (32-bit, signed)
  ConvertSignedIntToUnsignedInt ((INT32)INT32_MIN);
  // 1000: implicit conversion from type '{{.*}}' (aka 'int') of value -2147483648 (32-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 2147483648 (32-bit, unsigned)
  ConvertSignedIntToUnsignedChar ((INT32)(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  // 1100: implicit conversion from type '{{.*}}' (aka 'int') of value -2147483520 (32-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 128 (8-bit, unsigned)
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MIN);
  // 1200: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 128 (8-bit, unsigned)
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MIN);
  // 1300: implicit conversion from type '{{.*}}' (aka 'unsigned char') of value 128 (8-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MIN);
  // 1400: implicit conversion from type '{{.*}}' (aka '{{(signed )?}}char') of value -128 (8-bit, signed) to type '{{.*}}' (aka 'unsigned int') changed the value to 4294967168 (32-bit, unsigned)
  ConvertUnsignedIntToSignedChar ((((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  // 1500: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 2147483776 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32)(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  // 1600: implicit conversion from type '{{.*}}' (aka 'int') of value -2147483520 (32-bit, signed) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to -128 (8-bit, signed)
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  // All bits except the source and destination sign bits are set.

  /* For -fsanitize=implicit-conversion
     ubsan have no check 500, 1100, 1500, 1600

     For -fsanitize=implicit-integer-truncation
     500, 1100, 1500, 1600
  */

  // !!! Doesn't work or not hasn't been implemented yet

  DEBUG ((DEBUG_WARN, "UBT: Implicit-conversion when all bits except the source and destination \'Sign\' bits are set...\n"));

  ConvertUnsignedIntToUnsignedInt ((UINT32)INT32_MAX);
  ConvertUnsignedCharToUnsignedChar ((UINT8)INT8_MAX);
  ConvertSignedIntToSignedInt ((INT32)INT32_MAX);
  ConvertSignedCharToSignedChar ((INT8)INT8_MAX);
  ConvertUnsignedIntToUnsignedChar (~(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  ConvertUnsignedCharToUnsignedInt ((UINT8)INT8_MAX);
  ConvertUnsignedCharToSignedInt ((UINT8)INT8_MAX);
  ConvertSignedCharToSignedInt ((INT8)INT8_MAX);
  ConvertUnsignedIntToSignedInt ((UINT32)INT32_MAX);
  ConvertSignedIntToUnsignedInt ((INT32)INT32_MAX);
  ConvertSignedIntToUnsignedChar ((INT32)(~(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN))));
  // 1100: implicit conversion from type '{{.*}}' (aka 'int') of value 2147483519 (32-bit, signed) to type '{{.*}}' (aka 'unsigned char') changed the value to 127 (8-bit, unsigned)
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MAX);
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MAX);
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MAX);
  ConvertUnsignedIntToSignedChar (~(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  // 1500: implicit conversion from type '{{.*}}' (aka 'unsigned int') of value 2147483519 (32-bit, unsigned) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to 127 (8-bit, signed)
  ConvertSignedIntToSignedChar ((INT32) ~(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  // 1600: implicit conversion from type '{{.*}}' (aka 'int') of value 2147483519 (32-bit, signed) to type '{{.*}}' (aka '{{(signed )?}}char') changed the value to 127 (8-bit, signed)
  DEBUG ((DEBUG_INFO, "UBT: Done.\n\n\n"));

  ShiftOutOfBoundsCheck ();

  DEBUG ((DEBUG_INFO, "UBT: Completing testing cases with integer...\n\n\n\n\n"));
}
