#!/usr/bin/env python3
import sys
import xml.sax.saxutils
def main():
    arr=process_options()
    if all(cell is None for cell in arr):
        sys.exit()
    else:
        maxwidth=arr[0]
        formats=arr[1]
    print_start()
    count=0
    while True:
        try:
            line=input()
            if count==0:
                color="lightgreen"
            elif count%2:
                color="white"
            else:
                color="lightyellow"
            print_line(line,color,maxwidth,formats)
            count+=1
        except EOFError:
            break
    print_end()
def print_start():
    print("<table border='1'>")
def print_end():
    print("</table>")
def print_line(line,color,maxwidth,formats):
    print("<tr bgcolor='{0}'>".format(color))
    fields=extract_fields(line)
    for field in fields:
        if not field:
            print("<td></td>")
        else:
            number=field.replace(",","")
            try:
                x=float(number)
                print("<td align='right'>{0:{1}}</td>".format(x,formats))
            except ValueError:
                field=field.title()
                field=field.replace("And","and")
                if len(field)<=maxwidth:
                    field=xml.sax.saxutils.escape(field)
                else:
                    field="{0}...".format(xml.sax.saxutils.escape(field[0:maxwidth]))
                print("<td>{0}</td>".format(field))
    print("</tr>")
def extract_fields(line):
    fields=[]
    field=""
    quote=None
    for c in line:
        if c in "\"'":
            if quote is None:
                quote=c
            elif quote==c:
                quote=None
            else:
                field+=c
            continue
        if quote is None and c==",":
            fields.append(field)
            field=""
        else:
            field+=c
    if field:
        fields.append(field)
    return fields
def process_options():
    maxwidth=100
    formats=".0f"
    if "-h" in sys.argv or "--help" in sys.argv:
        print('''usage:
        csv2html.py [maxwidth=int] [formats=str] <infile.csv>outfile.html

        maxwidth is an optional integer;if specified, it sets the maximum
        number of characters that can be output for string fields,
        otherwise a default of 100 characters is used.

        formats is the format to use for numbers;if not specified it
        defaults to ".0f".''')
        maxwidth=None
        formats=None
    else:
        for arg in sys.argv:
            if arg.startswith("maxwidth="):
                _,value=arg.split("=",1)
                try:
                    maxwidth=int(value)
                except ValueError:
                    print("maxwidth不是有效整数，已忽略")
            elif arg.startswith("formats="):
                _,formats=arg.split("=",1)
    return maxwidth,formats
main()
