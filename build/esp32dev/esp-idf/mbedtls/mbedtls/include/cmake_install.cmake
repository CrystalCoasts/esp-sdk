# Install script for directory: /Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/build_info.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "/Users/diane/.platformio/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

