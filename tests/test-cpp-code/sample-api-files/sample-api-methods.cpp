#include "iostream"
#include "vector"
#include "utility"

#include "string"
#include "../../../include/crow_all.h"
using namespace std;

int main()
{
    /*
    SimpleApp class organizes all the different parts of Crow and 
    provides a simple interface to interact with these parts.
    */
    crow::SimpleApp app;

    // GET ROUTE
    CROW_ROUTE(app, "/api/welcome")([](){
        return "Landing page of the website";
    });

    // POST ROUTE (CREATE)
    CROW_ROUTE(app, "/api/create").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Body is empty");

        string dbName;
        try {
            dbName = body["database_name"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try{
            /*
            TODO:
                - Here cpp code goes to handle database creation using the name
            */
        }catch (const std::runtime_error &err) {
            return crow::response(500, "Server error");
        }
        return crow::response(200, "Database created");
    });

    // GET ROUTE (READ)
    CROW_ROUTE(app, "/api/read").methods(crow::HTTPMethod::GET)
    ([&](const crow::request& req){
        auto dbName = req.url_params.get("database_name");
        auto name = req.url_params.get("name");
        if (!name || !dbName)
            return crow::response(400, "Name parameter not set");
        try {
            /*
            TODO:
                - First check the database name
                - Try to find name in the database
                - Then send data respective to that name
            */
        } catch (const std::runtime_error &err) {
            string message = "Not able to find any database with such name";
            return crow::response(404, message);
        }

        return crow::response(200, "Yaha peh json data daalna hain with all data");
    });

    // PATCH ROUTE (UPDATE)
    CROW_ROUTE(app, "/api/update").methods(crow::HTTPMethod::PATCH)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Body is empty/ No data given");
        string name, age, weight;
        try {
            name = body["name"].s();
            age = body["age"].s();
            weight = body["weight"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try{
            /*
            TODO:
                - Yaha peh database mein insert karna ka code
            */
        }
        catch (const std::runtime_error &err) {
            return crow::response(500, "Server Error");
        }
        
        return crow::response(200, "Data added");
    });

    // DELETE ROUTE (DELETE)
    CROW_ROUTE(app, "/api/update").methods(crow::HTTPMethod::DELETE)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Body is empty");
        string name;
        try {
            name = body["name"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }
        try{
            /*
            TODO:
                - CPP code to delete from database
            */
        } catch (const std::runtime_error &err) {
            return crow::response(500, "Server error");
        }
        return crow::response(200, "Data deleted");
    });

    // CROW_ROUTE(app, "/api/blogs")
    // ([&]()
    // {
    //     auto r1 = redisClient.lrange("titles", 0, -1);
    //     auto r2 = redisClient.lrange("contents", 0, -1);
    //     redisClient.sync_commit();
    //     r1.wait();
    //     r2.wait();
    //     auto r = r1.get().as_array();
    //     std::vector<std::string> titles(r.size()), contents(r.size());
    //     std::transform(r.begin(), r.end(), titles.begin(), [](const cpp_redis::reply &rep) { return rep.as_string(); });

    //     auto rC = r2.get().as_array();
    //     std::transform(rC.begin(), rC.end(), contents.begin(), [](const cpp_redis::reply &rep) { return rep.as_string(); });

    //     std::vector<crow::json::wvalue> blogs;
    //     for (int i = 0; i < titles.size(); i++)
    //     {
    //         blogs.push_back(crow::json::wvalue{
    //             {"title", titles[i]},
    //             {"content", contents[i]}
    //         });
    //     }

    //     return crow::json::wvalue{{"data", blogs}};
    // });

    app.port(3000).multithreaded().run();
}