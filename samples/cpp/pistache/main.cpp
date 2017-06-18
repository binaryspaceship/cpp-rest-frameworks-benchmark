#include <pistache/endpoint.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>

using namespace rapidjson;
using namespace Net;
using namespace std;

class HelloHandler : public Http::Handler {
public:

    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(
        const Http::Request& request, 
        Http::ResponseWriter response
    ) {
        char _id[20];
        
        StringBuffer JSONStrBuffer;
        Writer<StringBuffer> writer(JSONStrBuffer);
        writer.StartArray(); 
    
        for (int i = 0; i < 10000; ++i) {
            writer.StartObject(); 
            snprintf(_id, sizeof(_id), "item-%d", i);
            writer.Key("id"); writer.String(_id);
            writer.Key("name"); writer.String("Hello World");
            writer.Key("type"); writer.String("application");
            writer.EndObject();
        }
        writer.EndArray();

        response.send(Http::Code::Ok, JSONStrBuffer.GetString());
    }
};

int main() {
    Net::Address addr(Net::Ipv4::any(), Net::Port(9000));
    auto opts = Net::Http::Endpoint::options()
        .threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serve();

    server.shutdown();
}