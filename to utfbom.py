import codecs

ansi_file_path = "localisation/english/state_names_l_english.yml"
utf8_bom_file_path = "localisation/english/state_names_l_english.yml"

with codecs.open(ansi_file_path, "r", encoding="cp1252") as ansi_file:
    content = ansi_file.read()

with codecs.open(utf8_bom_file_path, "w", encoding="utf-8-sig") as utf8_bom_file:
    utf8_bom_file.write(content)
print("converted")
