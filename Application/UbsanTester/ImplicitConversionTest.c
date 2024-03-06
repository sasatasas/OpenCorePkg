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

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when all bits are not set...\n\n\n"));
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
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when all bits are not set are done...\n\n\n\n\n"));


  // One lowest bit set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when one lowest bit set...\n\n\n"));
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
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when one lowest bit set are done...\n\n\n\n\n"));


  // All source bits set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when all source bits set...\n\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)UINT32_MAX);
  ConvertUnsignedCharToUnsignedChar ((UINT8)UINT8_MAX);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)UINT32_MAX);
  ConvertSignedCharToSignedChar ((INT8)UINT8_MAX);
  ConvertUnsignedIntToUnsignedChar ((UINT32)UINT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967295 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)UINT8_MAX);
  ConvertUnsignedCharToSignedInt ((UINT8)UINT8_MAX);
  ConvertSignedCharToSignedInt ((INT8)UINT8_MAX);
  ConvertUnsignedIntToSignedInt ((UINT32)UINT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967295 to type 'INT32' (aka 'int') changed the value to -1\n\n"));
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)UINT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -1 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967295\n\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)UINT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -1 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n\n"));
  ConvertSignedCharToUnsignedChar ((INT8)UINT8_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)UINT8_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n\n"));
  ConvertSignedCharToUnsignedInt ((INT8)UINT8_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967295\n\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)UINT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967295 to type 'INT8' (aka 'signed char') changed the value to -1\n\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)UINT32_MAX);
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when all source bits set are done...\n\n\n\n\n"));


  // Source 'Sign' bit set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when source 'Sign' bit set...\n\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)INT32_MIN);
  ConvertUnsignedCharToUnsignedChar ((UINT8)INT8_MIN);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)INT32_MIN);
  ConvertSignedCharToSignedChar ((INT8)INT8_MIN);
  ConvertUnsignedIntToUnsignedChar ((UINT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'UINT8' (aka 'unsigned char') changed the value to 0\n\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)INT8_MIN);
  ConvertUnsignedCharToSignedInt ((UINT8)INT8_MIN);
  ConvertSignedCharToSignedInt ((INT8)INT8_MIN);
  ConvertUnsignedIntToSignedInt ((UINT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'INT32' (aka 'int') changed the value to -2147483648\n\n"));
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'UINT32' (aka 'unsigned int') changed the value to 2147483648\n\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'UINT8' (aka 'unsigned char') changed the value to 0\n\n"));
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'INT8' (aka 'signed char') changed the value to 0\n\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'INT8' (aka 'signed char') changed the value to 0\n\n"));
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when source 'Sign' bit set are done...\n\n\n\n\n"));

  // All bits except the source 'Sign' bit are set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when all bits except the source 'Sign' bit are set...\n\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)INT32_MAX);
  ConvertUnsignedCharToUnsignedChar ((UINT8)INT8_MAX);
  ConvertSignedIntToSignedInt ((INT32)(UINT32)INT32_MAX);
  ConvertSignedCharToSignedChar ((INT8)INT8_MAX);
  ConvertUnsignedIntToUnsignedChar ((UINT32)INT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483647 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)INT8_MAX);
  ConvertUnsignedCharToSignedInt ((UINT8)INT8_MAX);
  ConvertSignedCharToSignedInt ((INT8)INT8_MAX);
  ConvertUnsignedIntToSignedInt ((UINT32)INT32_MAX);
  ConvertSignedIntToUnsignedInt ((INT32)(UINT32)INT32_MAX);
  ConvertSignedIntToUnsignedChar ((INT32)(UINT32)INT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483647 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n\n"));
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MAX);
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MAX);
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MAX);
  ConvertUnsignedIntToSignedChar ((UINT32)INT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483647 to type 'INT8' (aka 'signed char') changed the value to -1\n\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)INT32_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483647 to type 'INT8' (aka 'signed char') changed the value to -1\n\n"));
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when all bits except the source 'Sign' bit are set are done...\n\n\n\n\n"));

  // All destination bits set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when all destination bits set...\n\n\n"));
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
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT8' (aka 'unsigned char') changed the value to 255\n\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)UINT8_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n\n"));
  ConvertSignedCharToUnsignedInt ((INT8)UINT8_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -1 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967295\n\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)UINT8_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)UINT8_MAX);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value 255 to type 'INT8' (aka 'signed char') changed the value to -1\n\n"));
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when all destination bits set are done...\n\n\n\n\n"));

  // Destination 'sign' bit set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when destination 'sign' bit set...\n\n\n"));
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
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)(UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  ConvertSignedCharToUnsignedInt ((INT8)(UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n\n"));
  ConvertUnsignedIntToSignedChar ((UINT32)(UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  ConvertSignedIntToSignedChar ((INT32)(UINT32)(UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when destination 'sign' bit set are done...\n\n\n\n\n"));

  // All bits except the destination 'sign' bit are set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when all bits except the destination 'sign' bit are set...\n\n\n"));
  ConvertUnsignedIntToUnsignedInt ((~((UINT32)(UINT8)INT8_MIN)));
  ConvertUnsignedCharToUnsignedChar ((UINT8)(UINT8)INT8_MIN);
  ConvertSignedIntToSignedInt ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  ConvertSignedCharToSignedChar ((INT8)(UINT8)INT8_MIN);
  ConvertUnsignedIntToUnsignedChar ((~((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967167 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)(UINT8)INT8_MIN);
  ConvertUnsignedCharToSignedInt ((UINT8)(UINT8)INT8_MIN);
  ConvertSignedCharToSignedInt ((INT8)(UINT8)INT8_MIN);
  ConvertUnsignedIntToSignedInt ((~((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967167 to type 'INT32' (aka 'int') changed the value to -129\n\n"));
  ConvertSignedIntToUnsignedInt ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -129 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967167\n\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -129 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n\n"));
  ConvertSignedCharToUnsignedChar ((INT8)(UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)(UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  ConvertSignedCharToUnsignedInt ((INT8)(UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n\n"));
  ConvertUnsignedIntToSignedChar ((~((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 4294967167 to type 'INT8' (aka 'signed char') changed the value to 127\n\n"));
  ConvertSignedIntToSignedChar ((INT32)(~((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -129 to type 'INT8' (aka 'signed char') changed the value to 127\n\n"));
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when all bits except the destination 'sign' bit are set are done...\n\n\n\n\n"));

  // Only the source and destination sign bits are set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when only the source and destination sign bits are set...\n\n\n"));
  ConvertUnsignedIntToUnsignedInt ((UINT32)INT32_MIN);
  ConvertUnsignedCharToUnsignedChar ((UINT8)INT8_MIN);
  ConvertSignedIntToSignedInt ((INT32)INT32_MIN);
  ConvertSignedCharToSignedChar ((INT8)INT8_MIN);
  ConvertUnsignedIntToUnsignedChar (((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483776 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n\n"));
  ConvertUnsignedCharToUnsignedInt ((UINT8)INT8_MIN);
  ConvertUnsignedCharToSignedInt ((UINT8)INT8_MIN);
  ConvertSignedCharToSignedInt ((INT8)INT8_MIN);
  ConvertUnsignedIntToSignedInt ((UINT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483648 to type 'INT32' (aka 'int') changed the value to -2147483648\n\n"));
  ConvertSignedIntToUnsignedInt ((INT32)INT32_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483648 to type 'UINT32' (aka 'unsigned int') changed the value to 2147483648\n\n"));
  ConvertSignedIntToUnsignedChar ((INT32)(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483520 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n\n"));
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT8' (aka 'unsigned char') changed the value to 128\n\n"));
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT8' (aka 'unsigned char') of value 128 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MIN);
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT8' (aka 'signed char') of value -128 to type 'UINT32' (aka 'unsigned int') changed the value to 4294967168\n\n"));
  ConvertUnsignedIntToSignedChar ((((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483776 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  ConvertSignedIntToSignedChar ((INT32)(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value -2147483520 to type 'INT8' (aka 'signed char') changed the value to -128\n\n"));
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when only the source and destination sign bits are set are done...\n\n\n\n\n"));

  // All bits except the source and destination sign bits are set.
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion when all bits except the source and destination sign bits are set...\n\n\n"));
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
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483519 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483519 to type 'UINT8' (aka 'unsigned char') changed the value to 127\n\n"));
  ConvertSignedCharToUnsignedChar ((INT8)INT8_MAX);
  ConvertUnsignedCharToSignedChar ((UINT8)INT8_MAX);
  ConvertSignedCharToUnsignedInt ((INT8)INT8_MAX);
  ConvertUnsignedIntToSignedChar (~(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'UINT32' (aka 'unsigned int') of value 2147483519 to type 'INT8' (aka 'signed char') changed the value to 127\n\n"));
  ConvertSignedIntToSignedChar ((INT32) ~(((UINT32)INT32_MIN) | ((UINT32)(UINT8)INT8_MIN)));
  DEBUG ((DEBUG_WARN, "UBT: '{{.*}}' from type 'INT32' (aka 'int') of value 2147483519 to type 'INT8' (aka 'signed char') changed the value to 127\n\n"));
  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion when all bits except the source and destination sign bits are set are done...\n\n\n\n\n"));
}


VOID
EFIAPI
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

  DEBUG ((DEBUG_INFO, "UBT: Checks with integer overflow with abs are done are done...\n\n\n\n\n"));
}

VOID
EFIAPI
ImplicitConversionCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with implicit conversion...\n\n\n"));

  ConversionAndTruncationCheck ();

  DEBUG ((DEBUG_INFO, "UBT: Checks with implicit conversion are done...\n\n\n\n\n"));
}
