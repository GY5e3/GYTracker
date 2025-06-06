#pragma once

#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/component.hpp>
#include <userver/storages/redis/client.hpp>
#include <userver/storages/redis/component.hpp>
#include <userver/storages/secdist/component.hpp>
#include <userver/storages/secdist/provider_component.hpp>

namespace another_service {

class AnnounceHTTP final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-announce-http";

    using HttpHandlerBase::HttpHandlerBase;

    AnnounceHTTP(const userver::components::ComponentConfig& config,
                 const userver::components::ComponentContext& context);

    std::string HandleRequestThrow(const userver::server::http::HttpRequest&,
                                   userver::server::request::RequestContext&) const override;

private:
    const int m_interval = 600;

    const std::unordered_set<std::string> m_hardcodedInfoHashes {"00000000000000000000", "12345678901234567890"};

    userver::storages::redis::ClientPtr m_redisClient;
    userver::storages::redis::CommandControl m_redisCC;
};

}  // namespace another_service