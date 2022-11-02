#include "iostream"
#include "vector"
#include "utility"

#include "string"
#include "crow.h"

#include "../user-defined-header-files/hashing.h"

using namespace std;

int main() {
    
    hashTable* tablePointer = new hashTable();
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
    CROW_ROUTE(app, "/api/create_database")([&](const crow::request& req) {
        
        auto teacherName = req.url_params.get("teacher_name");

        if ( !teacherName ) {
            return crow::response(400, "Teacher name not specified.\n\n");
        }
            
        try{
            if( hashSearch(tablePointer, teacherName) ) {
                return crow::response(200, "Database already exists.\n\n");
            }

            insertDatabaseintoHashTable(tablePointer, teacherName, NULL);

            return crow::response(200, "Database created.\n\n");
            /*
            TODO:
                - Here cpp code goes to handle database creation using the name
            */
        }
        catch (const std::runtime_error &err) {
            return crow::response(500, "Internal Server Error.\n");
        }
    });

    // GET ROUTE (READ)
    CROW_ROUTE(app, "/api/display_student_record")([&](const crow::request& req) {

        auto teacherName = req.url_params.get("teacher_name");
        auto studentName = req.url_params.get("student_name");
        
        if ( !teacherName ) {
            return crow::response(400, "Teacher name parameter not set");
        }

        if ( !studentName ) {
            return crow::response(400, "Student name parameter not set");
        }
            
        try {
            hashTableItem* teacherHashValue = hashSearch(tablePointer, teacherName);
            
            if(!teacherHashValue) {
                return crow::response(404, "Database doesn't exist. Please make a create request first.\n");
            }
            
            Node* studentNode = searchNode(teacherHashValue->teacherDB, studentName);

            printf("%p", studentNode);

            if(!studentNode) {
                return crow::response(404, "Student record doesn't exist.\n");
            }   

            string message = "Teacher Name: " + string(teacherName) + "\nStudent Name: " + string(studentNode->name) + "\nAge: " + to_string(studentNode->age) + "\nWeight: " + to_string(studentNode->weight) + "\nCGPA: " + to_string(studentNode->cgpa) + "\n\n"; 
            
            return crow::response(200, message);

            /*
            TODO:
                - First check the database name
                - Try to find name in the database
                - Then send data respective to that name
            */
        } 
        catch (const std::runtime_error &err) {
            string message = "Internal Server Error";
            return crow::response(500, message);
        }
    });

    // GET ROUTE (READ)
    CROW_ROUTE(app, "/api/display_all_records")([&](const crow::request& req) {

        auto teacherName = req.url_params.get("teacher_name");

        if ( !teacherName ) {
            return crow::response(400, "Teacher name parameter not set");
        }

        try {
            hashTableItem* teacherHashValue = hashSearch(tablePointer, teacherName);
            
            if(!teacherHashValue) {
                return crow::response(404, "Database doesn't exist. Please make a create request first.\n");
            }

            string message = hashTableDisplayAllDatabaseRecords(tablePointer, teacherName);
            
            return crow::response(200, message + "\n");

            /*
            TODO:
                - First check the database name
                - Try to find name in the database
                - Then send data respective to that name
            */
        } 
        catch (const std::runtime_error &err) {
            string message = "Internal Server Error";
            return crow::response(500, message);
        }
    });

    // PATCH ROUTE (UPDATE)
    CROW_ROUTE(app, "/api/update_database_record")([&](const crow::request& req) {
        auto teacherName = req.url_params.get("teacher_name");
        char* studentName = req.url_params.get("student_name");
        auto age = req.url_params.get("age");
        auto weight = req.url_params.get("weight");
        auto cgpa = req.url_params.get("cgpa");
        
        if ( !teacherName || !studentName || !age || !weight || !cgpa ) {
            return crow::response(400, "Data incomplete.\n");
        }

        try{
           hashTableItem* teacherDB = hashSearch(tablePointer, teacherName);
           if(!teacherDB) {
                return crow::response(400, "Database doesn't exist. Please make a create request first.\n");
           }

           Node* studentNode = new Node;
           studentNode -> name = string(studentName);
           studentNode -> age = stoi(age, NULL);
           studentNode -> weight = strtod(weight, NULL);
           studentNode -> cgpa = strtod(cgpa, NULL);

           hashTableUpdateDatabaseRecords(tablePointer, teacherName, studentNode);
        }
        catch (const std::runtime_error &err) {
            return crow::response(500, studentName);
        }
        
        return crow::response(200, "Data added.\n\n");
    });

    // DELETE ROUTE (DELETE)
    CROW_ROUTE(app, "/api/delete_student_record")([&](const crow::request& req) {
        auto teacherName = req.url_params.get("teacher_name");
        auto studentName = req.url_params.get("student_name");

        if ( !studentName ) {
            
            return crow::response(400, "Name parameter not set.\n");
        }
        try {
            hashTableItem* teacherHashValue = hashSearch(tablePointer, teacherName);
            
            if(!teacherHashValue) {
                return crow::response(404, "Database doesn't exist. Please make a create request first.\n\n");
            }
            
            Node* studentNode = searchNode(teacherHashValue->teacherDB, studentName);

            if(!studentNode) {
                return crow::response(404, "Student record doesn't exist.\n\n");
            }   

            hashTableDeleteFromDatabase(tablePointer, teacherName, studentName);

            //TODO: 
            return crow::response(200, "Record deleted.\n\n");
        } 
        catch (const std::runtime_error &err) {
            string message = "Internal Server Error.\n";
            return crow::response(500, message);
        }
    });
    // DELETE ROUTE (DELETE)
    // CROW_ROUTE(app, "/api/update")([&](const crow::request& req)
    // {
    //     auto body = crow::json::load(req.body);
    //     if (!body)
    //         return crow::response(400, "Body is empty");
    //     string name;
    //     try {
    //         name = body["name"].s();
    //     } catch (const std::runtime_error &err) {
    //         return crow::response(400, "Invalid body");
    //     }
    //     try{
    //         /*
    //         TODO:
    //             - CPP code to delete from database
    //         */
    //     } catch (const std::runtime_error &err) {
    //         return crow::response(500, "Server error");
    //     }
    //     return crow::response(200, "Data deleted");
    // });

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