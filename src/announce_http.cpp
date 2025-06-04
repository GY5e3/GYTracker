#include <announce_http.hpp>

#include <greeting.hpp>

namespace another_service {

std::string AnnounceHTTP::HandleRequestThrow(const userver::server::http::HttpRequest& request, 
                                             userver::server::request::RequestContext&) const 
{
    std::string ans;
    std::unordered_map<std::string, std::vector<std::string>> mp
    {
        {"hash111", {"0.0.0.0:1233", "0.0.0.1:1233"}},
        {"hash112", {"0.1.0.0:1243", "0.0.0.1:1233"}}
    };

    if(request.HasArg("info_hash"))
    {
        const auto& it = mp.find(request.GetArg("info_hash"));

        if(it != end(mp))
        {
            ans.append("Peer list: ");
            for(const auto& peer : it->second)
            {
                ans.append(peer + "|");
            }
        }
        else
            return "Error: unknown info_hash\n";
    }
    else
        return "Error: missing info_hash\n";

    return "Hello, " + (request.HasArg("peer_id") ? request.GetArg("peer_id") : "unknown user") + "\n" + ans + "\n";
    
    //const std::string& info_hash = request.GetArg("info_hash");
    //const std::string& peer_id = request.GetArg("peer_id");
    //const int16_t port_str = std::stoi(request.GetArg("port"));
    //const std::string& ip = request.GetArg("ip");
    //const uint64_t uploaded = std::stoull(request.GetArg("uploaded"));
    //const uint64_t downloaded = std::stoull(request.GetArg("downloaded"));
    //const uint64_t left = std::stoull(request.GetArg("left"));
    //const std::string& event = request.GetArg("event");
}

}  // namespace another_service