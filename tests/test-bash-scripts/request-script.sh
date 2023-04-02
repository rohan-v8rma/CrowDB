#!/usr/bin/bash

# Currently, we are running this on local host. But, if we purchase or rent a domain name for our IP address, then we can make requests to that domain name, and it would be resolved using a DNS

#? NOTE: We have kept the Accept header as `text/plain` because our server is currently returning only strings. If we were to use this server in the real world, it would be more appropriate to return json, in which case Accept header would be `application/json`

<<IMP
* Just to be clear, 
- POST requests are used to create databases.
- PATCH requests are used to modify those databases by adding records to them.
- DELETE is used to delete records from those databases.
- GET is used to display single or multiple student records.
IMP

# Creating a database for a teacher (this is an entry in the hash table)
curl -X POST http://127.0.0.1:3000/api/create_database \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "rachna"}'

# Adding a record in database that has been added in the hash table in the previous command
curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "rachna", "student_name": "mayhul", "age": 19, "weight": 197, "cgpa": 9.7}'

# Displaying that student record
curl "http://127.0.0.1:3000/api/display_student_record?teacher_name=rachna&student_name=mayhul"

curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "rachna", "student_name": "rohan", "age": 20, "weight": 250, "cgpa": 9.5}'

curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "rachna", "student_name": "prerit", "age": 17, "weight": 150, "cgpa": 9.4}'

curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "rachna", "student_name": "soham", "age": 21, "weight": 350, "cgpa": 9.9}'


curl -X DELETE http://127.0.0.1:3000/api/delete_student_record \
-H "Accept: text/plain" \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "rachna", "student_name": "mayhul"}'

# GET method used by-default
curl "http://127.0.0.1:3000/api/display_student_record?teacher_name=rachna&student_name=mayhul"

# Hash Collision below
curl -X POST http://127.0.0.1:3000/api/create_database \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "archna"}'

# Adding student records for the second teacher
curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "archna", "student_name": "aakash", "age": 11, "weight": 250, "cgpa": 7.7}'

curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "archna", "student_name": "harry", "age": 14, "weight": 450, "cgpa": 7.0}'

curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
-H 'Accept: text/plain' \
-H 'Content-Type: application/json' \
-d '{"teacher_name": "archna", "student_name": "sameer", "age": 16, "weight": 192, "cgpa": 8.7}'

# Displaying records of the second teacher
curl "http://127.0.0.1:3000/api/display_all_records?teacher_name=archna"