#include <announce_http.hpp>

namespace another_service 
{
    AnnounceHTTP::AnnounceHTTP(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context)
        : userver::server::handlers::HttpHandlerBase(config, context),
        m_redisClient{
            context
                .FindComponent<userver::components::Redis>("key-value-database")
                .GetClient("taxi-tmp")},
        m_redisCC{std::chrono::seconds{15}, std::chrono::seconds{60}, 4} {}

    std::string AnnounceHTTP::HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                                 userver::server::request::RequestContext&) const 
    {
        const auto& info_hash = request.GetArg("info_hash");
        const auto& peer_id = request.GetArg("peer_id");
        const auto& ip = request.GetArg("ip");
        const auto& port = request.GetArg("port");
        const auto& uploaded = request.GetArg("uploaded");
        const auto& downloaded = request.GetArg("downloaded");
        const auto& left = request.GetArg("left");
        const auto& event = request.GetArg("event");

        // request.GetRemoteAddress();

        if (info_hash.empty() || peer_id.empty() || port.empty()) 
        {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::BadRequest);
            return {};
        }

        if(m_hardcodedInfoHashes.find(info_hash) == end(m_hardcodedInfoHashes))
        {
            return "d14:failure reason29:The torrent is not registerede";
        }

        m_redisClient->Sadd("peers:" + info_hash, peer_id, m_redisCC).Get();

        m_redisClient->Hset(peer_id + ":" + info_hash, "ip", ip, m_redisCC).Get();
        m_redisClient->Hset(peer_id + ":" + info_hash, "port", port, m_redisCC).Get();
        m_redisClient->Hset(peer_id + ":" + info_hash, "uploaded", uploaded, m_redisCC).Get();
        m_redisClient->Hset(peer_id + ":" + info_hash, "downloaded", downloaded, m_redisCC).Get();
        m_redisClient->Hset(peer_id + ":" + info_hash, "left", left, m_redisCC).Get();
        m_redisClient->Hset(peer_id + ":" + info_hash, "event", event, m_redisCC).Get();

        m_redisClient->Expire(peer_id + ":" + info_hash, std::chrono::seconds(900), m_redisCC).Get();

        std::string ans;


        return "Hello, " + (request.HasArg("peer_id") ? request.GetArg("peer_id") : "unknown user") + "\n";
    }

}  // namespace another_service