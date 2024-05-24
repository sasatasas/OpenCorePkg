#include "UbsanTester.h"

/*
 * Only Clang
 * Implicit conversion group of checks.
 *
 * Enables implicit-unsigned-integer-truncation, implicit-signed-integer-truncation,
 * and implicit-integer-sign-change.
 *
 * Use -fsanitize=implicit-conversion
 */

#ifdef __clang__

UINT32
EFIAPI
ConvertUnsignedIntToUnsignedInt (
  UINT32  X
  )
{
  #line 100
  return X;
}

UINT8
EFIAPI
ConvertUnsignedCharToUnsignedChar (
  UINT8  X
  )
{
  #line 200
  return X;
}

INT32
EFIAPI
ConvertSignedIntToSignedInt (
  INT32  X
  )
{
  #line 300
  return X;
}

INT8
EFIAPI
ConvertSignedCharToSignedChar (
  INT8  X
  )
{
  #line 400
  return X;
}

UINT8
EFIAPI
ConvertUnsignedIntToUnsignedChar (
  UINT32  X
  )
{
  #line 500
  return X;
}

UINT32
EFIAPI
ConvertUnsignedCharToUnsignedInt (
  UINT8  X
  )
{
  #line 600
  return X;
}

INT32
EFIAPI
ConvertUnsignedCharToSignedInt (
  UINT8  X
  )
{
  #line 700
  return X;
}

INT32
EFIAPI
ConvertSignedCharToSignedInt (
  INT8  X
  )
{
  #line 800
  return X;
}

INT32
EFIAPI
ConvertUnsignedIntToSignedInt (
  UINT32  X
  )
{
  #line 900
  return X;
}

UINT32
EFIAPI
ConvertSignedIntToUnsignedInt (
  INT32  X
  )
{
  #line 1000
  return X;
}

UINT8
EFIAPI
ConvertSignedIntToUnsignedChar (
  INT32  X
  )
{
  #line 1100
  return X;
}

UINT8
EFIAPI
ConvertSignedCharToUnsignedChar (
  INT8  X
  )
{
  #line 1200
  return X;
}

INT8
EFIAPI
ConvertUnsignedCharToSignedChar (
  UINT8  X
  )
{
  #line 1300
  return X;
}

UINT32
EFIAPI
ConvertSignedCharToUnsignedInt (
  INT8  X
  )
{
  #line 1400
  return X;
}

INT8
EFIAPI
ConvertUnsignedIntToSignedChar (
  UINT32  X
  )
{
  #line 1500
  return X;
}

INT8
EFIAPI
ConvertSignedIntToSignedChar (
  INT32  X
  )
{
  #line 1600
  return X;
}

VOID
EFIAPI
__attribute__ ((no_sanitize ("implicit-integer-sign-change")))
ConversionAndTruncationCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when all bits are not set...\n\n"));
  ConvertUnsignedIntToUnsignedInt (0);
  ConvertUnsignedCharToUnsignedChar (0);
  ConvertSignedIntToSignedInt (0);
  ConvertSignedCharToSignedChar (0);
  ConvertUnsignedIntToUnsignedChar (0);
  ConvertUnsignedCharToUnsignedInt (0);
  ConvertUnsignedCharToSignedInt (0);
  ConvertSignedCharToSignedInt (0);
  ConvertUnsignedIntToSignedInt (0);
  ConvertSignedIntToUnsignedInt (0);
  ConvertSignedIntToUnsignedChar (0);
  ConvertSignedCharToUnsignedChar (0);
  ConvertUnsignedCharToSignedChar (0);
  ConvertSignedCharToUnsignedInt (0);
  ConvertUnsignedIntToSignedChar (0);
  ConvertSignedIntToSignedChar (0);
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when all bits are not set are done...\n\n\n"));

  // One lowest bit set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when one lowest bit set...\n\n"));
  ConvertUnsignedIntToUnsignedInt (1);
  ConvertUnsignedCharToUnsignedChar (1);
  ConvertSignedIntToSignedInt (1);
  ConvertSignedCharToSignedChar (1);
  ConvertUnsignedIntToUnsignedChar (1);
  ConvertUnsignedCharToUnsignedInt (1);
  ConvertUnsignedCharToSignedInt (1);
  ConvertSignedCharToSignedInt (1);
  ConvertUnsignedIntToSignedInt (1);
  ConvertSignedIntToUnsignedInt (1);
  ConvertSignedIntToUnsignedChar (1);
  ConvertSignedCharToUnsignedChar (1);
  ConvertUnsignedCharToSignedChar (1);
  ConvertSignedCharToUnsignedInt (1);
  ConvertUnsignedIntToSignedChar (1);
  ConvertSignedIntToSignedChar (1);
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when one lowest bit set are done...\n\n\n"));

  // All source bits set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when all source bits set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)MAX_UINT32);
  ConvertUnsignedCharToUnsignedChar ((UINT8)MAX_UINT8);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)MAX_UINT32);
  ConvertSignedCharToSignedChar ((INT8)MAX_UINT8);
  ConvertUnsignedIntToUnsignedChar ((UINT32)MAX_UINT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967295 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)MAX_UINT8);
  ConvertUnsignedCharToSignedInt ((UINT8)MAX_UINT8);
  ConvertSignedCharToSignedInt ((INT8)MAX_UINT8);
  ConvertUnsignedIntToSignedInt ((UINT32)MAX_UINT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967295 to type 'INT32' (aka 'int') changed the value to -1\n"));
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)MAX_UINT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -1 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967295\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)MAX_UINT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -1 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n"));
  ConvertSignedCharToUnsignedChar ((INT8)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n"));
  ConvertSignedCharToUnsignedInt ((INT8)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967295\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)MAX_UINT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967295 to type 'INT8' (aka 'signed char') changed the value to -1\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)MAX_UINT32);
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when all source bits set are done...\n\n\n"));

  // Source 'Sign' bit set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when source 'Sign' bit set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)MIN_INT32);
  ConvertUnsignedCharToUnsignedChar ((UINT8)MIN_INT8);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)MIN_INT32);
  ConvertSignedCharToSignedChar ((INT8)MIN_INT8);
  ConvertUnsignedIntToUnsignedChar ((UINT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'UINT8' (aka 'unsigned char') changed the value to 0\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)MIN_INT8);
  ConvertUnsignedCharToSignedInt ((UINT8)MIN_INT8);
  ConvertSignedCharToSignedInt ((INT8)MIN_INT8);
  ConvertUnsignedIntToSignedInt ((UINT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'INT32' (aka 'int') changed the value to -2147483648\n"));
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'UINT32' (aka 'unsigned int') changed the value to 2147483648\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'UINT8' (aka 'unsigned char') changed the value to 0\n"));
  ConvertSignedCharToUnsignedChar ((INT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  ConvertSignedCharToUnsignedInt ((INT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'INT8' (aka 'signed char') changed the value to 0\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'INT8' (aka 'signed char') changed the value to 0\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when source 'Sign' bit set are done...\n\n\n"));

  // All bits except the source 'Sign' bit are set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when all bits except the source 'Sign' bit are set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)MAX_INT32);
  ConvertUnsignedCharToUnsignedChar ((UINT8)MAX_INT8);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)MAX_INT32);
  ConvertSignedCharToSignedChar ((INT8)MAX_INT8);
  ConvertUnsignedIntToUnsignedChar ((UINT32)MAX_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483647 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)MAX_INT8);
  ConvertUnsignedCharToSignedInt ((UINT8)MAX_INT8);
  ConvertSignedCharToSignedInt ((INT8)MAX_INT8);
  ConvertUnsignedIntToSignedInt ((UINT32)MAX_INT32);
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)MAX_INT32);
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)MAX_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483647 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n"));
  ConvertSignedCharToUnsignedChar ((INT8)MAX_INT8);
  ConvertUnsignedCharToSignedChar ((UINT8)MAX_INT8);
  ConvertSignedCharToUnsignedInt ((INT8)MAX_INT8);
  ConvertUnsignedIntToSignedChar ((UINT32)MAX_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483647 to type 'INT8' (aka 'signed char') changed the value to -1\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)MAX_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483647 to type 'INT8' (aka 'signed char') changed the value to -1\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when all bits except the source 'Sign' bit are set are done...\n\n\n"));

  // All destination bits set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when all destination bits set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)MAX_UINT8);
  ConvertUnsignedCharToUnsignedChar ((UINT8)MAX_UINT8);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)MAX_UINT8);
  ConvertSignedCharToSignedChar ((INT8)MAX_UINT8);
  ConvertUnsignedIntToUnsignedChar ((UINT32)MAX_UINT8);
  ConvertUnsignedCharToUnsignedInt ((UINT8)MAX_UINT8);
  ConvertUnsignedCharToSignedInt ((UINT8)MAX_UINT8);
  ConvertSignedCharToSignedInt ((INT8)MAX_UINT8);
  ConvertUnsignedIntToSignedInt ((UINT32)MAX_UINT8);
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)MAX_UINT8);
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)MAX_UINT8);
  ConvertSignedCharToUnsignedChar ((INT8)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n"));
  ConvertSignedCharToUnsignedInt ((INT8)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967295\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)MAX_UINT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when all destination bits set are done...\n\n\n"));

  // Destination 'sign' bit set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when destination 'sign' bit set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)(UINT8)MIN_INT8);
  ConvertUnsignedCharToUnsignedChar ((UINT8)(UINT8)MIN_INT8);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)(UINT8)MIN_INT8);
  ConvertSignedCharToSignedChar ((INT8)(UINT8)MIN_INT8);
  ConvertUnsignedIntToUnsignedChar ((UINT32)(UINT8)MIN_INT8);
  ConvertUnsignedCharToUnsignedInt ((UINT8)(UINT8)MIN_INT8);
  ConvertUnsignedCharToSignedInt ((UINT8)(UINT8)MIN_INT8);
  ConvertSignedCharToSignedInt ((INT8)(UINT8)MIN_INT8);
  ConvertUnsignedIntToSignedInt ((UINT32)(UINT8)MIN_INT8);
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)(UINT8)MIN_INT8);
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)(UINT8)MIN_INT8);
  ConvertSignedCharToUnsignedChar ((INT8)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  ConvertSignedCharToUnsignedInt ((INT8)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when destination 'sign' bit set are done...\n\n\n"));

  // All bits except the destination 'sign' bit are set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when all bits except the destination 'sign' bit are set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((~((UINT32)(UINT8)MIN_INT8)));
  ConvertUnsignedCharToUnsignedChar ((UINT8)(UINT8)MIN_INT8);
  ConvertSignedIntToSignedInt ((INT32)(~((UINT32)(UINT8)MIN_INT8)));
  ConvertSignedCharToSignedChar ((INT8)(UINT8)MIN_INT8);
  ConvertUnsignedIntToUnsignedChar ((~((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967167 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)(UINT8)MIN_INT8);
  ConvertUnsignedCharToSignedInt ((UINT8)(UINT8)MIN_INT8);
  ConvertSignedCharToSignedInt ((INT8)(UINT8)MIN_INT8);
  ConvertUnsignedIntToSignedInt ((~((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967167 to type 'INT32' (aka 'int') changed the value to -129\n"));
  ConvertSignedIntToUnsignedInt ((INT32)(~((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -129 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967167\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(~((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -129 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n"));
  ConvertSignedCharToUnsignedChar ((INT8)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  ConvertSignedCharToUnsignedInt ((INT8)(UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n"));
  ConvertUnsignedIntToSignedChar ((~((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967167 to type 'INT8' (aka 'signed char') changed the value to 127\n"));
  ConvertSignedIntToSignedChar ((INT32)(~((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -129 to type 'INT8' (aka 'signed char') changed the value to 127\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when all bits except the destination 'sign' bit are set are done...\n\n\n"));

  // Only the source and destination sign bits are set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when only the source and destination sign bits are set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)MIN_INT32);
  ConvertUnsignedCharToUnsignedChar ((UINT8)MIN_INT8);
  ConvertSignedIntToSignedInt ((INT32)MIN_INT32);
  ConvertSignedCharToSignedChar ((INT8)MIN_INT8);
  ConvertUnsignedIntToUnsignedChar (((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483776 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)MIN_INT8);
  ConvertUnsignedCharToSignedInt ((UINT8)MIN_INT8);
  ConvertSignedCharToSignedInt ((INT8)MIN_INT8);
  ConvertUnsignedIntToSignedInt ((UINT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'INT32' (aka 'int') changed the value to -2147483648\n"));
  ConvertSignedIntToUnsignedInt ((INT32)MIN_INT32);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'UINT32' (aka 'unsigned int') changed the value to 2147483648\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483520 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n"));
  ConvertSignedCharToUnsignedChar ((INT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  ConvertSignedCharToUnsignedInt ((INT8)MIN_INT8);
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n"));
  ConvertUnsignedIntToSignedChar ((((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483776 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  ConvertSignedIntToSignedChar ((INT32)(((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483520 to type 'INT8' (aka 'signed char') changed the value to -128\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when only the source and destination sign bits are set are done...\n\n\n"));

  // All bits except the source and destination sign bits are set.
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion when all bits except the source and destination sign bits are set...\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)MAX_INT32);
  ConvertUnsignedCharToUnsignedChar ((UINT8)MAX_INT8);
  ConvertSignedIntToSignedInt ((INT32)MAX_INT32);
  ConvertSignedCharToSignedChar ((INT8)MAX_INT8);
  ConvertUnsignedIntToUnsignedChar (~(((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8)));
  ConvertUnsignedCharToUnsignedInt ((UINT8)MAX_INT8);
  ConvertUnsignedCharToSignedInt ((UINT8)MAX_INT8);
  ConvertSignedCharToSignedInt ((INT8)MAX_INT8);
  ConvertUnsignedIntToSignedInt ((UINT32)MAX_INT32);
  ConvertSignedIntToUnsignedInt ((INT32)MAX_INT32);
  ConvertSignedIntToUnsignedChar ((INT32)(~(((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8))));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483519 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n"));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483519 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n"));
  ConvertSignedCharToUnsignedChar ((INT8)MAX_INT8);
  ConvertUnsignedCharToSignedChar ((UINT8)MAX_INT8);
  ConvertSignedCharToUnsignedInt ((INT8)MAX_INT8);
  ConvertUnsignedIntToSignedChar (~(((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483519 to type 'INT8' (aka 'signed char') changed the value to 127\n"));
  ConvertSignedIntToSignedChar ((INT32) ~(((UINT32)MIN_INT32) | ((UINT32)(UINT8)MIN_INT8)));
  DEBUG ((DEBUG_WARN, "\nUBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483519 to type 'INT8' (aka 'signed char') changed the value to 127\n"));
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion when all bits except the source and destination sign bits are set are done...\n\n\n"));
}

VOID
EFIAPI
ImplicitConversionCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with implicit conversion...\n\n"));

  ConversionAndTruncationCheck ();

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with implicit conversion are done...\n\n\n"));
}

#endif
