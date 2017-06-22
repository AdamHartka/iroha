/*
Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "validator.hpp"
#include <datetime/time.hpp>

namespace validator {
  namespace stateless {
    using Transaction = iroha::protocol::Transaction;
    auto log = logger::Logger("stateless validator");

    bool validate(const Transaction& tx) {
      log.debug("Is transaction not future?:{}", tx.header().created_time() <= iroha::time::now64());
      log.debug("Does transaction have a signature?:{}", tx.header().signature_size() != 0);
      log.debug("Is creator publicKey correct?:{} (length:{})", tx.body().creator_pubkey().size() == 32, tx.body().creator_pubkey().size());
      return
        tx.header().created_time() <= iroha::time::now64() && // 過去に作られたTxか // TODO: consider when to ignore transactions for being too old
        tx.header().signature_size() != 0                  && // 電子署名は含まれているか
        // TODO: calculate hash
        // TODO: verify the signature for each signature in the header
        tx.body().creator_pubkey().size() == 44;          // 公開鍵は32byteか ToDo configurable
    }
  };
};