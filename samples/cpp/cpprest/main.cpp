#include <cpprest/http_listener.h>
#include <cpprest/json.h>
 
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
 
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

/* handlers implementation */

void handle_get(const http_request& request)
{
    vector<json::value> values;
    values.reserve(10000);

    vector<pair<utility::string_t, json::value>> fields;
    fields.reserve(3);

    char _id[20];
 
    for (int i = 0; i < 10000; ++i) {
        snprintf(_id, sizeof(_id), "item-%d", i);
        fields.push_back(make_pair("id", json::value::string(_id)));
        fields.push_back(make_pair("name", json::value::string("Hello World")));
        fields.push_back(make_pair("type", json::value::string("application")));

        values.push_back(json::value::object(fields));
        fields.clear();
    }

    http_response response(status_codes::OK);
    response.headers().add("Connection", "keep-alive");
    response.set_body(json::value::array(values));

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