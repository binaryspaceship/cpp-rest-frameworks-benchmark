#include <cpprest/http_listener.h>
 
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
 
#include <iostream>
using namespace std;

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
using namespace rapidjson;

/* handlers implementation */

void handle_get(const http_request& request)
{
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

    http_response response(status_codes::OK);
    response.headers().add("Connection", "keep-alive");
    response.set_body(JSONStrBuffer.GetString());

    request.reply(response);
}
 
int main()
{
   http_listener listener("http://127.0.0.1:9000");
   listener.support(methods::GET, handle_get);
 
   try {
      listener
        .open()
        .wait();

      while (true);
   } catch (exception const & e) {
      cout << e.what() << endl;
   }

   listener
    .close()
    .wait();
 
   return 0;
}