#include <iostream>
#include <memory>
#include <cstdlib>
using namespace std;

#include <restbed>
using namespace restbed;

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
using namespace rapidjson;

void get_method_handler( const shared_ptr< Session > session )
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

    session->close(OK, JSONStrBuffer.GetString());
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 9000 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}