#!/usr/bin/bash

# Currently, we are running this on local host. But, if we purchase or rent a domain name for our IP address, then we can make requests to that domain name, and it would be resolved

curl "http://0.0.0.0:3000/api/create_db?teacher_name=rachna"

curl "http://0.0.0.0:3000/api/update_db?teacher_name=rachna&student_name=mayhul&age=19&weight=97&cgpa=9.7"

curl "http://0.0.0.0:3000/api/search_student_record?teacher_name=rachna&student_name=mayhul"
