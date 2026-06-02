#!/usr/bin/env python3
def extract_from_tag(tag,line):
    opener="<"+tag+">"
    closer="</"+tag+">"
    try:
        i=line.index(opener)
        start=i+len(opener)
        j=line.index(closer,start)
        return line[start:j]
    except ValueError:
        return None
s="<c>ssssd</c>"
print(extract_from_tag("c",s))
