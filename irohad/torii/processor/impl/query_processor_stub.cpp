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

#include <torii/processor/query_processor_stub.hpp>

namespace iroha {
  namespace torii {
    using rxcpp::subscriber;
    using std::shared_ptr;
    using model::Query;
    using model::QueryResponse;
    using model::Client;

    QueryProcessorStub::QueryProcessorStub(ametsuchi::WsvQuery &wsv,
                                           ametsuchi::BlockQuery &block) :
        wsv_(wsv), block_(block) {

    }

    void QueryProcessorStub::query_handle(model::Client client,
                                          const model::Query &query) {
      auto handle = handler_.find(query).value_or([](auto &) {
        std::cout << "[Q] Handler not found" << std::endl;
        return;
      });
      handle(query);
      return;
    }

    rxcpp::observable<shared_ptr<QueryResponse>>
    QueryProcessorStub::query_notifier() {
      return subject_.get_observable();
    }



  }  // namespace torii
}  // namespace iroha
