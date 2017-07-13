/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

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

//
// Created by Takumi Yamashita on 2017/04/28.
//

#ifndef IROHA_SYNCHRONIZATION_SYNCHRONIZATION_H
#define IROHA_SYNCHRONIZATION_SYNCHRONIZATION_H

#include <functional>
#include <queue>
#include <string>
#include <vector>

#include <model/model.hpp>

#include <network/sync_client.hpp>
#include <network/sync_gate.hpp>

#include <common/comparator.hpp>

namespace iroha {
  namespace synchronization {

    using Block = iroha::protocol::Block;

    // TODO
    class Synchronizer {
     public:
      // When commit block after consensus, invoke this function
      void on_commit(const Block& commited_block);

     private:
      // trigger call this.
      void startSync(const Block& commited_block);

      // startSync that two thread below.
      void fetchBlock(std::string ip, uint64_t offset);
      void syncObserve(uint64_t offset);

      // trigger call this.
      void finishSync();

      void clearCache();

      iroha::network::SyncClient client_;
      iroha::network::SyncGate gate_;

      std::priority_queue<Block, std::vector<Block>, comparator::BlockComparator> temp_block_;

      uint64_t current_;
      uint64_t upd_time_;
    };

  }  // namespace synchronization
}  // namespace iorha

#endif  // IROHA_SYNCHRONIZATION_SYNCHRONIZATION_H
