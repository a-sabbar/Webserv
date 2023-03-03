#!/usr/bin/python3

import cgi
import html

# Read the form data from standard input
form = cgi.FieldStorage()

# Get the form values
name = form.getvalue("name", "unkonwn")
email = form.getvalue("email", "unkonwn")

# print("Content-type: text/html")
# print("\r\n\r\n")

body = """
<html>
    <body>
        <h1>Form Results</h1>
        <p>name: {0}</p>
        <p>email: {1}</p>
    </body>
</html>
""".format(html.escape(name), html.escape(email))

# Output the HTML content
print(body)