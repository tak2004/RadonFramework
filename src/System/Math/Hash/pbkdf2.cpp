/*	$OpenBSD: pkcs5_pbkdf2.c,v 1.10 2017/04/18 04:06:21 deraadt Exp $
 */

/*-
 * Copyright (c) 2008 Damien Bergamini <damien.bergamini@free.fr>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <cstdint>

#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/Security.hpp"
#include "RadonFramework/backend/hashlib++/hl_sha1.h"

namespace RadonFramework::System::Math::Hash {

#define MINIMUM(a, b) (((a) < (b)) ? (a) : (b))

/*
 * HMAC-SHA-1 (from RFC 2202).
 */
void
hmac_sha1(const uint8_t* text, size_t text_len, const uint8_t* key,
          size_t key_len, uint8_t digest[SHA1HashSize])
{
  SHA1 sha1;
  HL_SHA1_CTX ctx;
  uint8_t k_pad[SHA1BlockSize];
  uint8_t tk[SHA1HashSize];
  int i;

  if (key_len > SHA1BlockSize) {
    sha1.SHA1Reset(&ctx);
    sha1.SHA1Input(&ctx, key, key_len);
    sha1.SHA1Result(&ctx, tk);

    key = tk;
    key_len = SHA1HashSize;
  }

  RF_SysMem::Set(k_pad, 0, SHA1BlockSize);
  RF_SysMem::Copy(k_pad, key, key_len);
  for (i = 0; i < SHA1BlockSize; i++)
    k_pad[i] ^= 0x36;

  sha1.SHA1Reset(&ctx);
  sha1.SHA1Input(&ctx, k_pad, SHA1BlockSize);
  sha1.SHA1Input(&ctx, text, text_len);
  sha1.SHA1Result(&ctx, digest);

  RF_SysMem::Set(k_pad, 0, SHA1BlockSize);
  RF_SysMem::Copy(k_pad, key, key_len);
  for (i = 0; i < SHA1BlockSize; i++)
    k_pad[i] ^= 0x5c;

  sha1.SHA1Reset(&ctx);
  sha1.SHA1Input(&ctx, k_pad, SHA1BlockSize);
  sha1.SHA1Input(&ctx, digest, SHA1HashSize);
  sha1.SHA1Result(&ctx, digest);
}

/*
 * Password-Based Key Derivation Function 2 (PKCS #5 v2.0).
 * Code based on IEEE Std 802.11-2007, Annex H.4.2.
 */
int
pkcs5_pbkdf2(const char* pass, size_t pass_len, const uint8_t* salt,
             size_t salt_len, uint8_t* key, size_t key_len, unsigned int rounds)
{
  uint8_t asalt[1024], obuf[SHA1HashSize];
  uint8_t d1[SHA1HashSize], d2[SHA1HashSize];
  unsigned int i, j;
  unsigned int count;
  size_t r;

  if (rounds < 1 || key_len == 0)
    return -1;
  if (salt_len == 0 || salt_len > SIZE_MAX - 4)
    return -1;
  if (salt_len > 1020)
    return -1;

  RF_SysMem::Copy(asalt, salt, salt_len);

  for (count = 1; key_len > 0; count++) {
    asalt[salt_len + 0] = (count >> 24) & 0xff;
    asalt[salt_len + 1] = (count >> 16) & 0xff;
    asalt[salt_len + 2] = (count >> 8) & 0xff;
    asalt[salt_len + 3] = count & 0xff;
    hmac_sha1(asalt, salt_len + 4, reinterpret_cast<const uint8_t*>(pass),
              pass_len, d1);
    RF_SysMem::Copy(obuf, d1, sizeof(obuf));

    for (i = 1; i < rounds; i++) {
      hmac_sha1(d1, sizeof(d1), reinterpret_cast<const uint8_t*>(pass),
                pass_len, d2);
      RF_SysMem::Copy(d1, d2, sizeof(d1));
      for (j = 0; j < sizeof(obuf); j++)
        obuf[j] ^= d1[j];
    }

    r = MINIMUM(key_len, SHA1HashSize);
    RF_SysMem::Copy(key, obuf, r);
    key += r;
    key_len -= r;
  };
  RF_SysMem::Set(asalt, 0, 1024);
  RF_SysSecurity::EnsureFillZeros(d1, SHA1HashSize);
  RF_SysSecurity::EnsureFillZeros(d2, SHA1HashSize);
  RF_SysSecurity::EnsureFillZeros(obuf, SHA1HashSize);

  return 0;
}
}
