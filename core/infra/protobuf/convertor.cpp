

#include "convertor.hpp"

#include <vector>
#include <tuple>

namespace convertor{

    using namespace transaction;
    using namespace command;
    using namespace event;

    namespace detail{

        Event::Asset encodeObject(object::Asset aAsset){
            Event::Asset asset;
            asset.set_domain(aAsset.domain);
            asset.set_name(aAsset.name);
            // TODO: asset.set_value(aAsset.value);
            return asset;
        }

        Event::Domain encodeObject(object::Domain aDomain){
            Event::Domain domain;
            domain.set_name(aDomain.name);
            domain.set_ownerpublickey(aDomain.ownerPublicKey);
            return domain;
        }

        Event::Account encodeObject(object::Account aAccount){
            Event::Account account;
            account.set_name(aAccount.name);
            account.set_publickey(aAccount.publicKey);
            for(auto&& as: aAccount.assets){
                Event::Asset asset;
                asset.set_name(std::get<0>(as));
                //asset.set_value(std::get<1>(as));
                account.add_assets()->CopyFrom(asset);
            }
            return account;
        }
        // ====== decode ======

        object::Asset decodeObject(Event::Asset aAsset){
            std::string domain = aAsset.domain();
            std::string name = aAsset.name();
            return object::Asset(
                    std::move(domain),
                    std::move(name),
                    123456, //aAsset.value(), // TODO: Replace with map object value
                    1//aAsset.precision()
            );
        }

        object::Account decodeObject(Event::Account aAccount){
            auto publicKey = aAccount.publickey();
            auto name = aAccount.name();
            std::vector<std::tuple<std::string, std::int64_t>> assets;
            for(const Event::Asset& as: aAccount.assets()) {
                assets.emplace_back(as.name(), 1);//as.value());
            }
            return object::Account(
                    std::move(publicKey),
                    std::move(name),
                    std::move(assets)
            );
        }


        template <>
        ConsensusEvent<Transaction<Transfer<object::Asset>>> decodeTransaction2ConsensusEvent(Event::Transaction tx){
            auto name = tx.asset().name();
            auto sender = tx.senderpubkey();
            auto issuer = tx.senderpubkey();
            auto receiver = tx.receivepubkey();
            auto res = ConsensusEvent<
                    Transaction<
                        Transfer<object::Asset>
                    >
                >(
                    std::move(issuer),
                    std::move(sender),
                    std::move(receiver),
                    std::move(name),
                    1//tx.asset().value()
                );
            res.timestamp = tx.timestamp();
            return res;
        }

        template <>
        ConsensusEvent<Transaction<Add<object::Asset>>> decodeTransaction2ConsensusEvent(Event::Transaction tx){
            auto name = tx.asset().name();
            auto domain = tx.asset().domain();
            auto issuer = tx.senderpubkey();
            auto res = ConsensusEvent<
                    Transaction<
                        Add<object::Asset>
                    >
                >(
                    std::move(issuer),
                    std::move(domain),
                    std::move(name),
                    1,//tx.asset().value(),
                    2//tx.asset().precision()
                );
            res.timestamp = tx.timestamp();
            return res;
        }

        template <>
        ConsensusEvent<Transaction<Add<object::Account>>> decodeTransaction2ConsensusEvent(Event::Transaction tx){
            auto name = tx.account().name();
            auto publicKey = tx.account().publickey();
            std::vector<std::tuple<std::string,long>> assets;
            for(auto&& as: tx.account().assets()){
                assets.emplace_back(as.name(), 1);//as.value());
            }
            auto issuer = tx.senderpubkey();
            auto res = ConsensusEvent<
                    Transaction<
                            Add<object::Account>
                    >
                >(
                    std::move(issuer),
                    std::move(publicKey),
                    std::move(name),
                    std::move(assets)
                );
            res.timestamp = tx.timestamp();
            return res;
        }



        template <>
        ConsensusEvent<Transaction<Update<object::Asset>>> decodeTransaction2ConsensusEvent(Event::Transaction tx){
            auto name = tx.asset().name();
            auto issuer = tx.senderpubkey();
            auto owner = tx.senderpubkey();
            auto res = ConsensusEvent<
                    Transaction<
                            Update<object::Asset>
                    >
                >(
                    std::move(issuer),
                    std::move(owner),
                    std::move(name),
                    1//tx.asset().value()
                );
            res.timestamp = tx.timestamp();
            return res;
        }

    }

};
