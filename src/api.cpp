#include "iostream"
#include "vector"
#include "utility"
#include "string"

//? Includes for building
// #include "crow_all.h"
// #include <hashing.h>

//? Includes for testing
#include "../include/crow_all.h"
#include "../include/hashing.h"

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
    CROW_ROUTE(app, "/api/create_database").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Body is empty.\n\n");

        string teacherName;
        try {
            teacherName = body["teacher_name"].s();
        } catch (const std::runtime_error &err) {
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
            return crow::response(500, "Internal Server Error.\n\n");
        }
        return crow::response(200, "Database created.\n\n");
    });


    // GET ROUTE (READ)    
    CROW_ROUTE(app, "/api/display_student_record")
    ([&](const crow::request& req) 
    {

        auto teacherName = req.url_params.get("teacher_name");
        auto studentName = req.url_params.get("student_name");
        
        if ( !teacherName ) {
            return crow::response(400, "Teacher name parameter not set.\n\n");
        }

        if ( !studentName ) {
            return crow::response(400, "Student name parameter not set.\n\n");
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
    CROW_ROUTE(app, "/api/display_all_records")
    ([&](const crow::request& req) 
    {

        auto teacherName = req.url_params.get("teacher_name");

        if ( !teacherName ) {
            return crow::response(400, "Teacher name parameter not set");
        }

        try {
            hashTableItem* teacherHashValue = hashSearch(tablePointer, teacherName);
            
            if(!teacherHashValue) {
                return crow::response(404, "Database doesn't exist. Please make a create request first.\n\n");
            }

            string message = hashTableDisplayAllDatabaseRecords(tablePointer, teacherName);
            
            return crow::response(200, message + "\n");

            /*
            TODO:
                - First check the database name
                - Send all names in that database
            */
        } 
        catch (const std::runtime_error &err) {
            string message = "Internal Server Error.\n\n";
            return crow::response(500, message);
        }
    });

    // PATCH ROUTE (UPDATE)
    CROW_ROUTE(app, "/api/update_database_record").methods(crow::HTTPMethod::PATCH)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Body is empty/No data given.\n\n");
        }
        string 
            teacherName, 
            studentName;
        
        int age;
        
        double
            cgpa,
            weight;
        
        try {
            teacherName = body["teacher_name"].s();
            studentName = body["student_name"].s();
            age = body["age"].i();
            cgpa = body["cgpa"].d();
            weight = body["weight"].d();
            
        } 
        catch (const std::runtime_error &err) {
            return crow::response(400, "Data incomplete.\n\n");
        }

        try{
           hashTableItem* teacherDB = hashSearch(tablePointer, teacherName);
           if(!teacherDB) {
                return crow::response(400, "Database doesn't exist. Please make a create request first.\n\n");
           }

           Node* studentNode = new Node;
           studentNode -> name = string(studentName);
           studentNode -> age = age;
           studentNode -> weight = weight;
           studentNode -> cgpa = cgpa;

           hashTableUpdateDatabaseRecords(tablePointer, teacherName, studentNode);

           /*
            TODO:
                - Inserting to database
            */
        }
        catch (const std::runtime_error &err) {
            return crow::response(500, "Server Error.\n\n");
            // return crow::response(500, studentName);
        }
        
        return crow::response(200, "Data added.\n\n");
    });

    // DELETE ROUTE (DELETE)
    CROW_ROUTE(app, "/api/delete_student_record").methods(crow::HTTPMethod::DELETE)
    ([&](const crow::request& req) 
    {
        
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Body is empty.\n\n");
        }
        
        string 
            teacherName, 
            studentName;

        try {
            teacherName = body["teacher_name"].s();
            studentName = body["student_name"].s();
        } 
        catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body.\n\n");
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
            string message = "Internal Server Error.\n\n";
            return crow::response(500, message);
        }
        return crow::response(200, "Data deleted.\n\n");
    });

    app.port(3000).multithreaded().run();
}
