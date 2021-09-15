#ifndef __ECDSA_KEY_H__
#define __ECDSA_KEY_H__

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

#include "secp256k1.h"

#include "pub_key.h"

namespace ecdsa {

class Key {
 public:
  /**
   * @brief Create a new private key.
   *
   * @return Key object created.
   */
  Key();

  /**
   * @brief Import an existing private key.
   *
   * @param priv_key_data Private key data.
   *
   * @return Key object created.
   */
  Key(const std::vector<uint8_t> &priv_key_data);

  /// Destructor.
  ~Key();

  /// Get private key data.
  const std::vector<uint8_t> &get_priv_key_data() const {
    return priv_key_data_;
  }

  /// Get public key data.
  const std::vector<uint8_t> &get_pub_key_data() const { return pub_key_data_; }

  /**
   * @brief Verify key is valid or not.
   *
   * @return Returns true if current private key is valid.
   */
  bool VerifyKey() const;

  /**
   * @brief Create a public key.
   *
   * @return Public key object.
   */
  PubKey CreatePubKey() const;

  /**
   * @brief Make a signature
   *
   * @param hash Hash value.
   *
   * @return Signature return.
   */
  std::tuple<std::vector<uint8_t>, bool> Sign(
      const std::vector<uint8_t> &hash) const;

  bool CalculatePublicKey(bool compressed);

 private:
  secp256k1_context *ctx_ = nullptr;
  std::vector<uint8_t> priv_key_data_;
  std::vector<uint8_t> pub_key_data_;
};

}  // namespace ecdsa

#endif
