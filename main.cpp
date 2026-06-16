#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <stdio.h>

#include "json.hpp"
#include "httplib.h"

using namespace nlohmann;
using namespace std;
using namespace httplib;

Server svr;
Client cli("discord.com");

bool to_bot(json &data){
    string payload = data.dump();

    auto result = cli.Post(getenv("DISCORD_WH"), payload, "application/json");

    if (result && result->status == 200){
        return true;
    }

    return false;
}

void handle_alert(const Request &req, Response &res){
    json body = json::parse(req.body);
    if (body.contains("is_test") && body["is_test"] == true){
        res.set_content("works", "text/plain");
    }
}

int main(){
    svr.Post("/sentinel", handle_alert);
    svr.listen("0.0.0.0", 8080);

    exit(0);
}