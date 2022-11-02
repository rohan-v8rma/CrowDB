#!/usr/bin/bash

# Currently, we are running this on local host. But, if we purchase or rent a domain name for our IP address, then we can make requests to that domain name, and it would be resolved

curl "http://127.0.0.1:3000/api/create_database?teacher_name=rachna"

curl "http://127.0.0.1:3000/api/create_database?teacher_name=rachna"

curl "http://127.0.0.1:3000/api/update_database_record?teacher_name=rachna&student_name=mayhul&age=19&weight=197&cgpa=9.7"

curl "http://127.0.0.1:3000/api/display_student_record?teacher_name=rachna&student_name=mayhul"

curl "http://127.0.0.1:3000/api/delete_student_record?teacher_name=rachna&student_name=mayhul" 

curl "http://127.0.0.1:3000/api/display_student_record?teacher_name=rachna&student_name=mayhul"
