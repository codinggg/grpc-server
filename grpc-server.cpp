#ifndef PROTOBUF_USE_DLLS 
#define PROTOBUF_USE_DLLS 
#endif

#include <iostream>
#include <grpc++/grpc++.h>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include "addressbook.grpc.pb.h"

using namespace std;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class SearchRequestImpl final : public SearchService::Service{
    grpc::Status Search(ServerContext* context, const SearchRequest* request,
        SearchResponse* reply) override {
        string prefix("hello ");
        reply->set_response(prefix + request->request());
        return Status::OK;
    }
};

void runServer() {
    string server_address("0.0.0.0:50051");
    SearchRequestImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << endl;

    server->Wait();
}

int main()
{
    std::cout << "Hello World!\n";
    runServer();

    return 0;
}
