#!/usr/bin/bash

# Currently, we are running this on local host. But, if we purchase or rent a domain name for our IP address, then we can make requests to that domain name, and it would be resolved

curl "http://127.0.0.1:3000/api/create_database?teacher_name=rachna"

curl "http://127.0.0.1:3000/api/create_database?teacher_name=rachna"

curl "http://127.0.0.1:3000/api/update_database_record?teacher_name=rachna&student_name=mayhul&age=19&weight=197&cgpa=9.7"

curl "http://127.0.0.1:3000/api/display_student_record?teacher_name=rachna&student_name=mayhul"

curl "http://127.0.0.1:3000/api/update_database_record?teacher_name=rachna&student_name=rohan&age=20&weight=190&cgpa=9.6"

curl "http://127.0.0.1:3000/api/update_database_record?teacher_name=rachna&student_name=prerit&age=17&weight=150&cgpa=9.4"

curl "http://127.0.0.1:3000/api/update_database_record?teacher_name=rachna&student_name=soham&age=21&weight=200&cgpa=9.9"

curl "http://127.0.0.1:3000/api/display_all_records?teacher_name=rachna"

curl "http://127.0.0.1:3000/api/delete_student_record?teacher_name=rachna&student_name=mayhul" 

curl "http://127.0.0.1:3000/api/display_student_record?teacher_name=rachna&student_name=mayhul"
