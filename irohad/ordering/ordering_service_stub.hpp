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

#ifndef IROHA_ORDERING_SERVICE_STUB_HPP
#define IROHA_ORDERING_SERVICE_STUB_HPP

#include <network/ordering_gate.hpp>

namespace iroha {
  namespace network {
    class OrderingGateStub : public OrderingGate {
     public:
      void propagate_transaction(const model::Transaction &transaction) override;
      rxcpp::observable<model::Proposal> on_proposal() override;
     private:
      rxcpp::subjects::subject<model::Proposal> proposals_;
    };
  }//namespace network
}// namespace iroha

#endif //IROHA_ORDERING_SERVICE_STUB_HPP
