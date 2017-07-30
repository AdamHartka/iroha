/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_RAW_BLOCK_INSERTION_HPP
#define IROHA_RAW_BLOCK_INSERTION_HPP

#include <string>
#include <nonstd/optional.hpp>
#include "model/block.hpp"
#include "ametsuchi/storage.hpp"
#include <vector>
#include <memory>

namespace iroha {
  namespace main {
    /**
     * Class provide functionality to insert blocks to storage
     * without any validation.
     * This class will be useful for creating test environment
     * and testing pipeline.
     */
    class BlockInserter {
     public:
      BlockInserter(std::shared_ptr<ametsuchi::Storage> storage);

      /**
       * Parse block from file
       * @param path - path with tagret block
       * @return object if operation done successfully, nullopt otherwice
       */
      nonstd::optional<model::Block> parseBlock(std::string path);

      /**
       * Apply block to current state of ledger
       * @param blocks - list of blocks for insertion
       */
      void appyToLedger(std::vector<model::Block> blocks);

     private:

      nonstd::optional<std::string> loadFile(std::string &path);

      nonstd::optional<std::vector<uint8_t>> convertString(std::string &value);

      std::shared_ptr<ametsuchi::Storage> storage_;
    };

  } // namespace main
} // namespace iroha
#endif //IROHA_RAW_BLOCK_INSERTION_HPP